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

constexpr std::string_view to_string(EventType type) {
  switch (type) {
  case EventType::commit_comment:
    return "Commit Comment";
  case EventType::create:
    return "Create";
  case EventType::delete_event:
    return "Delete Event";
  case EventType::discussion:
    return "Discussion";
  case EventType::fork:
    return "Fork";
  case EventType::gollum:
    return "Gollum";
  case EventType::issue_comment:
    return "Issue Comment";
  case EventType::issues:
    return "Issues";
  case EventType::member:
    return "Member";
  case EventType::public_event:
    return "Public Event";
  case EventType::pull_request:
    return "Pull Request";
  case EventType::pull_request_review:
    return "Pull Request Review";
  case EventType::pull_request_review_comment:
    return "Pull Request Review Comment";
  case EventType::push:
    return "Push";
  case EventType::release:
    return "Release";
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
  int total_events = 0;
  std::string name;
  std::unordered_map<EventType, int> event_counts;
};

struct DayContribution {
  int count;
  std::chrono::year_month_day date;
};

} // namespace Github
