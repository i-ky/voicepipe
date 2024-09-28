#include <string.h>

#include "../common/file_descriptor.hpp"
#include "signal.hpp"
#include "socket.hpp"

using std::vector;

int main(int argc, char *argv[]) {
  ConnectedSocket s;
  SignalFileDescriptor ss;

  vector<iovec> v;
  v.reserve(argc);

  while (*argv != nullptr) {
    v.push_back({*argv, strlen(*argv) + 1});
    argv++;
  }

  s.sendmsg(std::move(v));

  while (true) {
    FileDescriptor::select({&s, &ss, &StdIn});

    if (s) {
      s.forward(StdOut);
      // TODO stderr
    }

    if (ss) {
      ss.forward(s);
    }

    if (StdIn) {
      if (StdIn.forward(s) == 0) {
        break;
      }
    }
  }

  return 0;
}
