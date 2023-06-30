#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H 1

#include "../netFramework/Buffer.hpp"
#include "Header.hpp"
#include "URL.hpp"

namespace net::http {

class HttpRequest {
public:
  static HttpRequest create(const utils::URL &url) {
    HttpHeader header = HttpHeader::create(url.getPath());
    header.setHost(url.getHost());
    header.setAccept("*/*");
    header.setUserAgent("adjcjbc");
    HttpRequest request = HttpRequest(header, url);
    request.content = net::ImmutableAllocBuffer::create(0);
    return request;
  }

  void setContent(net::ImmutableBuffer_p &&buffer) {
    content = std::move(buffer);
  }

  HttpHeader &getHeader() { return header; }

  MutableAllocBuffer_p build() const {
    std::string headerStr = header.build();

    size_t totalSize = headerStr.length() + content->size();
    MutableAllocBuffer_p result =
        MutableAllocBuffer::create(totalSize);

    memcpy(result->get(), headerStr.data(), headerStr.size());
    memcpy(((char *)result->get()) + headerStr.length(), content->get(),
           content->size());
    return result;
  }

  const utils::URL& getUrl() const {
	  return url;
  }

private:
  HttpRequest(HttpHeader header, utils::URL url) : header(header), url(url) {}
  HttpHeader header;
  utils::URL url;
  net::ImmutableBuffer_p content;
};

}; // namespace net::http

#endif /* end of include guard: HTTPREQUEST_H */
