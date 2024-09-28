#include "signal.hpp"

#include <stdio.h>

#include <sys/signalfd.h>

SignalSet::SignalSet() {
  if (sigfillset(&sg) == -1) {
    perror("cannot sigfillset()");
    throw;
  }
}

SignalSet::~SignalSet() = default;

SignalSet::operator const sigset_t *() const { return &sg; }

SignalFileDescriptor::SignalFileDescriptor()
    : FileDescriptor(signalfd(-1, sg, 0)) {
  if (fd == -1) {
    perror("cannot signalfd()");
    throw;
  }

  if (sigprocmask(SIG_BLOCK, sg, nullptr) == -1) {
    perror("cannot sigprocmask()");
    throw;
  }
}

SignalFileDescriptor::~SignalFileDescriptor() = default;

const SignalSet SignalFileDescriptor::sg;
