
#include "github_client.h"
#include "https_client.h"

#include <nlohmann/json.hpp>

#include <format>

GithubClient::GithubClient(HttpsClient& client) : m_client(client) {}

std::unordered_map<std::string, RepoStats>
GithubClient::get_events(std::string username) {
  const std::string url =
      "https://api.github.com/users/" + username + "/events";

  std::vector<std::string> headers = {"Accept: application/vnd.github+json",
                                      "X-GitHub-Api-Version: 2026-03-10",
                                      std::format("User-Agent: {}", username)};

  const auto response = m_client.get(url, headers);

  // Do parsing
  const auto data = nlohmann::json::parse(response);

  std::unordered_map<std::string, RepoStats> stats;

  for (const auto& event : data) {
    auto repo = event["repo"].value("name", "");
    auto type = event.value("type", "");

    if (type == "PushEvent")
      stats[repo].push_events++;
    else if (type == "PullRequestEvent")
      stats[repo].pull_request_events++;
    else if (type == "IssuesEvent")
      stats[repo].issues_events++;
  }
  return stats;
}
