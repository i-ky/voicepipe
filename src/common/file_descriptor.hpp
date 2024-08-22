#pragma once

#include <cstddef>
#include <string>

class FileDescriptor {
  class Iterator {
  public:
    [[nodiscard]] Iterator(int);
    ~Iterator();
    [[nodiscard]] std::string operator*() const;
    Iterator &operator++();
    [[nodiscard]] bool operator!=(std::nullptr_t);

  private:
    std::string v;
    const int fd;
  };

public:
  [[nodiscard]] FileDescriptor(int);
  ~FileDescriptor();
  [[nodiscard]] Iterator begin() const;
  [[nodiscard]] std::nullptr_t end() const;
  void write(const std::string &);

protected:
  const int fd;
};
