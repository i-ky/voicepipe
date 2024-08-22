#include "file_descriptor.hpp"

#include <stdio.h>
#include <unistd.h>

FileDescriptor::Iterator::Iterator(int fd) : fd(fd) {}

FileDescriptor::Iterator::~Iterator() = default;

std::string FileDescriptor::Iterator::operator*() const { return std::move(v); }

auto FileDescriptor::Iterator::operator++() -> Iterator & { return *this; }

bool FileDescriptor::Iterator::operator!=(std::nullptr_t) {
  char b[1024];

  const auto n = read(fd, b, sizeof(b));

  switch (n) {
  case -1:
    perror("cannot read()");
    throw;
  case 0:
    return false;
  default:
    v.assign(b, /*static_cast<std::size_t>*/ (n));
    return true;
  }
}

FileDescriptor::FileDescriptor(int fd) : fd(fd) {}

FileDescriptor::~FileDescriptor() {
  if (close(fd) == -1) {
    perror("cannot close()");
  }
}

auto FileDescriptor::begin() const -> Iterator { return fd; }

std::nullptr_t FileDescriptor::end() const { return nullptr; }

void FileDescriptor::write(const std::string &s) {
  if (::write(fd, s.data(), s.size()) == -1) {
    perror("cannot write()");
    throw;
  }
}
