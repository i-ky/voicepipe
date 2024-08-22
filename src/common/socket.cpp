#include "socket.hpp"

#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>

Socket::Socket() : FileDescriptor(socket(AF_UNIX, SOCK_SEQPACKET, 0)) {
  if (fd == -1) {
    perror("cannot socket()");
    throw;
  }
}

Socket::~Socket() {
  if (unlink("/tmp/voicepipe.sock") == -1) {
    perror("cannot unlink()");
  }
}
