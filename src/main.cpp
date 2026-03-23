
#include "https_client.h"

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>

constexpr int MAX_USERNAME_LENGTH = 39;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: github-activity <username>\n\n";
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

  const std::string url =
      "https://api.github.com/users/" + username + "/events";

  // Fix headers so it's compatible with the API
  std::vector<std::string> headers = {"Accept: application/vnd.github+json",
                                      "X-GitHub-Api-Version: 2026-03-10",
                                      "User-Agent: dtjandra888"}; // TODO: change to github app

  HttpsClient client{};
  auto response = client.get(url, headers);

  std::cout << response << "\n";

  return 0;
}
