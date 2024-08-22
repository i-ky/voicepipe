#include "socket.hpp"

int main() {
  ListeningSocket s;

  while (true) {
    auto c{s.accept()};

    for (auto m : c) {
      c.write(m);
    }
  }

  return 0;
}
