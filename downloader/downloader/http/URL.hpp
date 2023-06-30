#ifndef URL_H
#define URL_H 1

#include "../netFramework/NetDefs.hpp"

#include <algorithm>
#include <string.h>
#include <string>

namespace net::utils {

class URL {
public:
  static URL from(std::string &url) { return URL(url); }
  URL(const std::string &url) {
    size_t indexOf = url.find("://");
    if (indexOf != url.npos) {
      protocol.assign(url.cbegin(), url.cbegin() + indexOf);
      std::string tempPath("");
      tempPath.assign(url.cbegin() + indexOf + 3, url.cend());

      auto result = splitHostPath(tempPath, protocol);
      host = result.first.first;
      port = result.first.second;
      path = result.second;
    } else {
      protocol = std::string("http");
      path = std::string(url);

      auto result = splitHostPath(url, protocol);
      host = result.first.first;
      port = result.first.second;
      path = result.second;
    }
  }

  std::string getProtocol() { return protocol; }
  std::string getPath() { return path; }
  std::string getHost() { return host; }
  port_t getPort() const { return port; }

  const std::string getProtocol() const { return protocol; }
  const std::string getPath() const { return path; }
  const std::string getHost() const { return host; }

private:
  std::string protocol, path, host;
  port_t port;

  static port_t getDefaultPort(const std::string protocol) {
    port_t port;
    if (protocol == "http")
      port = 80;
    else if (protocol == "https")
      port = 443;
    else
      fprintf(stderr, "Unknow Protocol %s\n", protocol.data());
    return port;
  }

  static std::pair<std::string, port_t>
  solveHostPort(const std::string &host, const std::string &protocol) {
    size_t d = host.find(":");
    if (d == host.npos) {
      return std::make_pair(host, getDefaultPort(protocol));
    }
    std::string result("");
    result.assign(host.cbegin(), host.cbegin() + d);
    std::string port_str("");
    port_str.assign(host.cbegin() + d + 1, host.cend());
    return std::make_pair(result, (port_t)atoi(port_str.data()));
  }

  static std::pair<std::pair<std::string, port_t>, std::string>
  splitHostPath(const std::string &path, const std::string protocol) {
    size_t sp = path.find("/");
    if (sp != path.npos) {
      std::string host("");
      host.assign(path.cbegin(), path.cbegin() + sp);
      std::string result_path("");
      result_path.assign(path.cbegin() + sp, path.cend());
      return std::make_pair(solveHostPort(host, protocol), result_path);
    } else {
      return std::make_pair(solveHostPort(path, protocol), "/");
    }
  }
};

}; // namespace net::utils

#endif /* end of include guard: URL_H */
