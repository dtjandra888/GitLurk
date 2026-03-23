
#include <curl/curl.h>
#include <iostream>
#include <string>

constexpr int MAX_USERNAME_LENGTH = 39;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: github-activity <username>";
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

  // Main curl object
  CURL* curl;

  // Enum holding any error codes
  // curl_global_init must always be called before making requests
  CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
  if (result != CURLE_OK) {
    return (int)result;
  }

  curl = curl_easy_init();
  if (!curl) {
    std::cout << "Curl init failed\n";
    curl_global_cleanup();
    return 1;
  }

  const std::string url = "https://api.github.com/users/" + username + "/events";

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  // From libcurl example
#ifdef SKIP_PEER_VERIFICATION
  /*
   * If you want to connect to a site who is not using a certificate that is
   * signed by one of the certs in the CA bundle you have, you can skip the
   * verification of the server's certificate. This makes the connection
   * A LOT LESS SECURE.
   *
   * If you have a CA cert for the server stored someplace else than in the
   * default bundle, then the CURLOPT_CAPATH option might come handy for
   * you.
   */
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
  /*
   * If the site you are connecting to uses a different hostname than what
   * they have mentioned in their server certificate's commonName (or
   * subjectAltName) fields, libcurl refuses to connect. You can skip this
   * check, but it makes the connection insecure.
   */
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

  // Cache certs for a week
  curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);

  // Fix headers so it's compatible with the API
  struct curl_slist* chunk = nullptr;
  chunk = curl_slist_append(chunk, "Accept: application/vnd.github+json");
  chunk = curl_slist_append(chunk, "X-GitHub-Api-Version: 2026-03-10");
  chunk = curl_slist_append(chunk, "User-Agent: dtjandra888");

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

  result = curl_easy_perform(curl);

  if (result != CURLE_OK) {
    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result)
              << "\n";
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return 0;
}
