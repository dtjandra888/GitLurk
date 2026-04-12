
#include "github_client.h"
#include "https_client.h"

#include <curl/curl.h>
#include <format>
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
  GithubClient client{https};

  const auto events = client.get_events(username);

  for (const auto& [repo_name, stats] : events) {
    std::cout << std::format("Events for {}:\n  {} Push Events\n  {} Pull "
                             "Requests\n  {} Issues Events\n\n",
                             repo_name, stats.push_events,
                             stats.pull_request_events, stats.issues_events);
  }

  return 0;
}
