
#include "event_aggregator.h"

#include <map>
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

std::vector<Github::DayContribution> EventAggregator::aggregate_by_day(
    const std::vector<Github::GithubEvent>& events) {

  std::map<std::chrono::year_month_day, int> counts;
  for (const auto& event : events) {
    auto day_tp = std::chrono::floor<std::chrono::days>(event.timestamp);

    auto day = std::chrono::year_month_day{std::chrono::sys_days{day_tp}};

    counts[day]++;
  }

  std::vector<Github::DayContribution> result;
  result.reserve(counts.size());

  for (const auto& [date, count] : counts) {
    result.push_back({count, date});
  }
  return result;
}
