
#include "github_client.h"
#include "https_client.h"
#include "github.h"

#include <nlohmann/json.hpp>

#include <chrono>
#include <format>
#include <sstream>

namespace {
/// Parse Github timestamp string (ISO8601)
std::chrono::system_clock::time_point parse_time(const std::string& s) {
  std::chrono::system_clock::time_point tp;
  std::istringstream iss(s);

  iss >> std::chrono::parse("%Y-%m-%dT%H:%M:%SZ", tp);

  return tp;
}
} // namespace

namespace Github {

GithubClient::GithubClient(HttpsClient& client) : m_client(client) {}

std::optional<std::vector<GithubEvent>>
GithubClient::get_events(std::string username) {
  const std::string url =
      "https://api.github.com/users/" + username + "/events";

  std::vector<std::string> headers = {"Accept: application/vnd.github+json",
                                      "X-GitHub-Api-Version: 2026-03-10",
                                      std::format("User-Agent: {}", username)};

  const auto response = m_client.get(url, headers);

  // Do parsing
  const auto data = nlohmann::json::parse(response);

  // User not found
  if (data.is_object() && data.contains("message")) {
    return std::nullopt;
  }

  // User has no data
  if (data.empty()) {
    return std::vector<GithubEvent>{};
  }

  std::vector<GithubEvent> events;
  for (const auto& event : data) {
    events.emplace_back();
    auto& e = events.back();
    e.actor = event["actor"].value("login", username);
    e.repo = event["repo"].value("name", "");
    e.type = event["type"];
    e.timestamp = parse_time(event["created_at"]);
  }
  return events;
}
} // namespace Github
