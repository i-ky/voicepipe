#include "socket.hpp"

#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>

ListeningSocket::ListeningSocket() {
  const sockaddr_un a{AF_UNIX, "/tmp/voicepipe.sock"};

  if (bind(fd, reinterpret_cast<const sockaddr *>(&a), sizeof(a)) == -1) {
    perror("cannot bind()");
    throw;
  }

  if (listen(fd, 16) == -1) {
    perror("cannot listen()");
    throw;
  }
}

ListeningSocket::~ListeningSocket() = default;

auto ListeningSocket::accept() const -> ConnectedSocket {
  const auto ss = ::accept(fd, nullptr, 0);

  if (ss == -1) {
    perror("cannot accept()");
    throw;
  }

  return ss;
}
