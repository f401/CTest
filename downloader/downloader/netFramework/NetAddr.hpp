#ifndef NETADDR_H
#define NETADDR_H

#include "DomainNameServer.hpp"
#include <stdint.h>
#include <string.h>

namespace net {
class Address {
public:
  static Address create(IP_t ip, port_t port,
                        const DNSServer &server = DNSServer()) {
    Address addr(strdup(server.process(ip)), port);
    return addr;
  }

  const IP_t getIP() const { return ip; }
  const port_t getPort() const { return port; }
  IP_t getIP() { return ip; }
  port_t &getPort() { return port; }

  virtual ~Address() { delete ip; }

protected:
  Address(IP_t ip, port_t port) : ip(ip), port(port) {}

  IP_t ip; // Must be number
  port_t port;
};
} // namespace downloader

#endif /* end of include guard: NETADDR_H */
