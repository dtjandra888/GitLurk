#pragma once

#include <chrono>
#include <string>

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

} // namespace Github
