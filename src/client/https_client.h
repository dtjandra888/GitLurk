#pragma once

#include <string>
#include <vector>

class HttpsClient {
public:
  HttpsClient();
  ~HttpsClient();

  std::string get(const std::string& url,
                  const std::vector<std::string>& headers = {});

private:
  void* m_curl; // This is a CURL object;
};
