#ifndef NETADDR_H
#define NETADDR_H

#include "DomainNameServer.hpp"
#include "UniquePointer.hpp"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

namespace net {
class Address {
public:
  static Address* create(IP_t ip, port_t port,
                        const DNSServer &server = DNSServer()) noexcept {
    return new Address(strdup(server.process(ip)), port);
  }

  IP_t getIP() const noexcept { return ip; }
  port_t getPort() const noexcept { return port; }
  IP_t getIP() noexcept { return ip; }
  port_t &getPort() noexcept { return port; }

  virtual ~Address() noexcept { delete ip; }

  virtual in_addr_t getInternetAddress() const noexcept {
    return ::inet_addr(ip);
  };

  virtual port_t getEndianPort() const noexcept { return ::htons(port); }

protected:
  Address(IP_t ip, port_t port) noexcept : ip(ip), port(port) {}
  IP_t ip; // Must be number in `.`
  port_t port;
};

class AddrInetAny : public Address {
public:
  static AddrInetAny* create(port_t port) { return new AddrInetAny(port); }

  virtual in_addr_t getInternetAddress() const noexcept override {
    return ::htonl(INADDR_ANY);
  }

protected:
  AddrInetAny(port_t port) noexcept : Address(strdup("0.0.0.0"), port) {}
};

typedef utils::UniquePointer<Address> Address_p;
} // namespace net

#endif /* end of include guard: NETADDR_H */
