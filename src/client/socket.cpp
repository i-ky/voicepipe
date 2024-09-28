#include "socket.hpp"

#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <vector>

ConnectedSocket::ConnectedSocket() {
  const sockaddr_un a{AF_UNIX, "/tmp/voicepipe.sock"};

  if (connect(fd, reinterpret_cast<const sockaddr *>(&a), sizeof(a)) == -1) {
    perror("cannot connect()");
    throw;
  }
}

ConnectedSocket::~ConnectedSocket() = default;

void ConnectedSocket::sendmsg(std::vector<iovec> &&v) {
  msghdr m{nullptr, 0, v.data(), v.size(), nullptr, 0, 0};

  if (::sendmsg(fd, &m, 0) == -1) {
    perror("cannot sendmsg()");
    throw;
  }
}
