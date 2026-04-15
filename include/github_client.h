#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>

class HttpsClient;

namespace Github {

enum class EventType {
  commit_comment,
  create,
  delete_event,
  discussion,
  fork,
  gollum,
  issue_comment,
  issues,
  member,
  public_event,
  pull_request,
  pull_request_review,
  pull_request_review_comment,
  push,
  release,
  watch
};

struct GithubEvent {
  std::string actor;
  std::string repo;
  EventType type;
  std::chrono::system_clock::time_point timestamp;
};

class GithubClient {
public:
  GithubClient(HttpsClient& client);

  std::optional<std::vector<GithubEvent>> get_events(std::string username);

private:
  HttpsClient& m_client;
};

} // namespace Github
