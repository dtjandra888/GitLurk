
#include "https_client.h"

#include <curl/curl.h>
#include <stdexcept>
#include <string>
#include <vector>

/// Callback for CURLOPT_WRITEFUNCTION
static size_t write_to_string(void* ptr, size_t size, size_t count,
                              void* stream) {
  ((std::string*)stream)->append((char*)ptr, 0, size * count);
  return size * count;
}

HttpsClient::HttpsClient() {
  // curl_global_init must always be called before making requests
  CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
  if (result != CURLE_OK) {
    throw std::runtime_error("Failed to global init curl");
  }

  m_curl = curl_easy_init();
  if (!m_curl) {
    curl_global_cleanup();
    throw std::runtime_error("Failed to init curl");
  }

  // Cache certs for a week
  curl_easy_setopt(m_curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);

  // From libcurl example; Settings for HTTPS
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
}

HttpsClient::~HttpsClient() {
  curl_easy_cleanup(m_curl);
  curl_global_cleanup();
}

std::string HttpsClient::get(const std::string& url,
                             const std::vector<std::string>& headers) {
  std::string response;

  curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects
  curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_to_string);
  curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response);

  // Set headers
  struct curl_slist* chunk = nullptr;
  for (const auto& header : headers) {
    chunk = curl_slist_append(chunk, header.c_str());
  }
  if (chunk != nullptr) {
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, chunk);
  }

  auto result = curl_easy_perform(m_curl);

  // free headers request sent
  if (chunk != nullptr) {
    curl_slist_free_all(chunk);
  }

  if (result != CURLE_OK) {
    throw std::runtime_error(curl_easy_strerror(result));
  }

  return response;
}
