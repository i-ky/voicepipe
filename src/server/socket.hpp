#pragma once

#include "../common/file_descriptor.hpp"
#include "../common/socket.hpp"

class ListeningSocket : Socket {
  class ConnectedSocket : public FileDescriptor {
  public:
    using FileDescriptor::FileDescriptor;
  };

public:
  [[nodiscard]] ListeningSocket();
  ~ListeningSocket();
  [[nodiscard]] ConnectedSocket accept() const;
};
