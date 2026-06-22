#pragma once

#include <chrono>
#include <string>
#include <unordered_map>

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

// TODO: implement other less common events
constexpr std::string_view to_string(EventType type)
{
    switch (type) {
        case EventType::push:
            return "Push";
        case EventType::pull_request:
            return "PullRequest";
        case EventType::create:
            return "Create";
        case EventType::fork:
            return "Fork";
        case EventType::watch:
            return "Watch";
        default:
            return "Unknown";
    }
}

struct GithubEvent {
  std::string actor;
  std::string repo;
  EventType type;
  std::chrono::system_clock::time_point timestamp;
};

struct RepoSummary {
    std::string name;
    int total_events = 0;
    std::unordered_map<EventType, int> event_counts;
};

} // namespace Github
