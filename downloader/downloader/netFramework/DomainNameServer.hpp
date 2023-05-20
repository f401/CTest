#ifndef DOMAINNAMESERVER_H
#define DOMAINNAMESERVER_H

extern "C" {
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
}

#include "NetDefs.hpp"
#include "PrintUtils.hpp"

namespace net {
class DNSServer {
public:
  DNSServer() = default;

  virtual IP_t process(const IP_t ip) const {
    struct ::hostent *target = ::gethostbyname(ip);
    if (target == nullptr) {
      utils::printSystemError("DNS Failed");
      return nullptr;
    }
    return ::inet_ntoa(*(struct ::in_addr *)target->h_addr_list[0]);
  }
};
} // namespace downloader

#endif /* end of inlude guard: DOMAINNAMESERVER_H */
