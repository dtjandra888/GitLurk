#pragma once

#include <string>
#include <vector>

struct GithubEvent {
    std::string type;
    std::string repo;
    std::string user;
    std::string created_at;
};

class HttpsClient;

class GithubClient {
public:
  GithubClient(HttpsClient& client);

  std::vector<GithubEvent> get_events(std::string username);

private:
  HttpsClient& m_client;
};
