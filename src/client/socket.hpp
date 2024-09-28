#pragma once

#include <sys/uio.h>

#include <vector>

#include "../common/socket.hpp"

class ConnectedSocket : public Socket {
public:
  [[nodiscard]] ConnectedSocket();
  ~ConnectedSocket();
  void sendmsg(std::vector<iovec> &&);
};
