#pragma once

#include <sys/select.h>

#include <cstddef>
#include <initializer_list>
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

  class Select {
  public:
    void operator()(std::initializer_list<FileDescriptor *>);
    [[nodiscard]] bool ready(const FileDescriptor &) const;

  private:
    fd_set fds;
  };

public:
  [[nodiscard]] FileDescriptor(int);
  ~FileDescriptor();
  [[nodiscard]] Iterator begin() const;
  [[nodiscard]] std::nullptr_t end() const;
  void write(const std::string &);
  ssize_t forward(FileDescriptor &);
  [[nodiscard]] operator bool() const;

  static Select select;

protected:
  const int fd;
};

extern FileDescriptor StdIn;
extern FileDescriptor StdOut;
extern FileDescriptor StdErr;
