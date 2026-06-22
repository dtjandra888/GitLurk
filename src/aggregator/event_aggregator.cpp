
#include "event_aggregator.h"

#include <unordered_map>

std::vector<Github::RepoSummary>
EventAggregator::aggregate(const std::vector<Github::GithubEvent>& events) {

  std::unordered_map<std::string, Github::RepoSummary> summaries;
  for (const auto& event : events) {
    auto& repo = summaries[event.repo];

    repo.name = event.repo;
    repo.event_counts[event.type]++;
    repo.total_events++;
  }

  std::vector<Github::RepoSummary> results;

  for (auto& [_, summary] : summaries) {
    results.push_back(std::move(summary));
  }

  return results;
}
