
#include "client/github_client.h"
#include "client/https_client.h"

#include <iostream>
#include <string>

constexpr int MAX_USERNAME_LENGTH = 39;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: gitlurk <username>\n\n";
    return 1;
  }
  std::string username{argv[1]};
  if (username.empty()) {
    std::cerr << "Username is empty\n";
    return 1;
  }

  if (username.size() > MAX_USERNAME_LENGTH) {
    std::cerr << "Username is over the character limit\n";
    return 1;
  }

  HttpsClient https{};
//   Github::GithubClient client{https};
// 
//   const auto events_opt = client.get_events(username);
// 
//   if (!events_opt.has_value()) {
//     std::cerr << "Username was not found on Github\n";
//     return 1;
//   }
// 
//   const auto events = events_opt.value();
// 
//   if (events.empty()) {
//     std::cout << std::format("No data for {}\n", username);
//     return 0;
//   }
// 
//   for (const auto& [actor, repo, event, timestamp] : events) {
// 
//     std::cout << std::format(
//         "Event for {}:\n  Event type: {}\n  Timestamp: {}\n\n", repo,
//         stats.push_events, stats.pull_request_events, stats.issues_events);
//   }

  return 0;
}
