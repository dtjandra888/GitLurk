
#include "github.h"

class EventAggregator {
public:
  static std::vector<Github::RepoSummary>
  aggregate(const std::vector<Github::GithubEvent>& events);
  static std::vector<Github::DayContribution>
  aggregate_by_day(const std::vector<Github::GithubEvent>& events);
};
