
#include "github.h"

class EventAggregator {
public:
    static std::vector<Github::RepoSummary> aggregate(const std::vector<Github::GithubEvent>& events);
private:
};
