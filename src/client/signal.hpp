#pragma once

#include <signal.h>

#include "../common/file_descriptor.hpp"

class SignalSet {
public:
  [[nodiscard]] SignalSet();
  ~SignalSet();
  [[nodiscard]] operator const sigset_t *() const;

private:
  sigset_t sg;
};

class SignalFileDescriptor : public FileDescriptor {
public:
  [[nodiscard]] SignalFileDescriptor();
  ~SignalFileDescriptor();

private:
  static const SignalSet sg;
};
