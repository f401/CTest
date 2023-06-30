#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <map>
#include <string>

namespace net::http {

class HttpHeader {
public:
  static constexpr const std::string_view METHOD_GET = "GET";
  static constexpr const std::string_view METHOD_POST = "POST";

  static constexpr const std::string_view HTTP_NEWLINE = "\r\n";

  static HttpHeader create(std::string path,
                           std::string_view method = METHOD_GET) {
    return HttpHeader(path, METHOD_GET);
  }

  void putAttribute(std::string key, std::string value) {
    attrs.insert(std::make_pair(key, value));
  }

  void setUserAgent(std::string agent) {
    attrs.insert(std::make_pair("User-Agent", agent));
  }

  void setAccept(std::string accepts) {
    attrs.insert(std::make_pair("Accept", accepts));
  }

  void setHost(std::string host) {
    attrs.insert(std::make_pair("Host", host));
  }

  std::string_view getHost() {
	  return attrs["Host"];
  }

  std::string build() const {
    std::string result(
        std::string(method).append(" ").append(path).append(" HTTP/1.1").append(HTTP_NEWLINE));
    for (auto &[key, value] : attrs) {
      result = result.append(key).append(": ").append(value).append(HTTP_NEWLINE);
    }
    return result.append(HTTP_NEWLINE);
  }

private:
  HttpHeader(std::string path, std::string_view method)
      : path(path), method(method) {}

  std::map<std::string, std::string> attrs;
  std::string path;
  std::string_view method;
};

} // namespace net::http
#endif /* end of include guard: HEADER_H */
