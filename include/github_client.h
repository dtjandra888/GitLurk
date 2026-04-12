#pragma once

#include <string>
#include <unordered_map>

struct RepoStats {
  int push_events = 0;
  int pull_request_events = 0;
  int issues_events = 0;
};

class HttpsClient;

class GithubClient {
public:
  GithubClient(HttpsClient& client);

  std::unordered_map<std::string, RepoStats> get_events(std::string username);

private:
  HttpsClient& m_client;
};
