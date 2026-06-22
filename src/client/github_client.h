#pragma once

#include "github.h"

#include <optional>
#include <string>
#include <vector>

class HttpsClient;

namespace Github {

class GithubClient {
public:
  GithubClient(HttpsClient& client);

  std::optional<std::vector<GithubEvent>> get_events(std::string username);

private:
  HttpsClient& m_client;
};

} // namespace Github
