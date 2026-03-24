
#include "github_client.h"
#include "https_client.h"

#include <nlohmann/json.hpp>

GithubClient::GithubClient(HttpsClient& client) : m_client(client) {}

std::vector<GithubEvent> GithubClient::get_events(std::string username) {
  const std::string url =
      "https://api.github.com/users/" + username + "/events";

  std::vector<std::string> headers = {
      "Accept: application/vnd.github+json", "X-GitHub-Api-Version: 2026-03-10",
      "User-Agent: dtjandra888"}; // TODO: change to github app

  const auto response = m_client.get(url, headers);

  // Do parsing
  const auto data = nlohmann::json::parse(response);

  std::vector<GithubEvent> events;

  for (const auto& event : data) {
    GithubEvent e;
    e.type = event.value("type", "");
    e.repo = event["repo"].value("name", "");
    e.user = event["actor"].value("login", "");
    e.created_at = event.value("created_at", "");
    events.push_back(e);
  }
  return events;
}
