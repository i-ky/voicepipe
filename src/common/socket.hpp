#pragma once

#include "file_descriptor.hpp"

class Socket : public FileDescriptor {
public:
  [[nodiscard]] Socket();
  ~Socket();
};
