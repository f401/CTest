#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <algorithm>
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

  static HttpHeader from(char (*reader)(void *), void *param = nullptr) {
    std::string firstLine = readLine(reader, param);
    auto firstSpace = std::find(firstLine.cbegin(), firstLine.cend(), ' ');

    std::string path(""), method("");
    method.assign(firstLine.cbegin(), firstSpace);
    path.assign(firstSpace + 1, std::find(firstSpace + 1, firstLine.cend(), ' '));

    HttpHeader header = create(path, method);
    for (;;) {
	std::string str = readLine(reader, param);

	if (str.empty())
		break;
	size_t sp = str.find(": ");

	std::string key, value;
	key.assign(str.cbegin(), str.cbegin() + sp);
	value.assign(str.cbegin() + sp + 2, str.cend());

	header.putAttribute(key, value);
    }

    return header;
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

  void setHost(std::string host) { attrs.insert(std::make_pair("Host", host)); }

  std::string_view getHost() { return attrs["Host"]; }

  std::string build() const {
    std::string result(std::string(method)
                           .append(" ")
                           .append(path)
                           .append(" HTTP/1.1")
                           .append(HTTP_NEWLINE));
    for (auto &[key, value] : attrs) {
      result =
          result.append(key).append(": ").append(value).append(HTTP_NEWLINE);
    }
    return result.append(HTTP_NEWLINE);
  }

private:
  static std::string readLine(char (*reader)(void *), void *param) {
    char before, curr;
    std::string result;
    result.reserve(10);
    for (before = curr = 0;; ) {
      curr = (*reader)(param);
      if (before == '\r' && curr == '\n') {
        break;
      }
      result.append({curr});
      before = curr;
    }
    if (!result.empty())
    	result.pop_back();
    return result;
  }

  HttpHeader(std::string path, std::string_view method)
      : path(path), method(method) {}

  std::map<std::string, std::string> attrs;
  std::string path;
  std::string_view method;
};

} // namespace net::http
#endif /* end of include guard: HEADER_H */
