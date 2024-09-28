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

void FileDescriptor::Select::operator()(
    std::initializer_list<FileDescriptor *> l) {
  FD_ZERO(&fds);
  int max = 0;

  for (auto fd : l) {
    FD_SET(fd->fd, &fds);

    if (fd->fd > max) {
      max = fd->fd;
    }
  }

  if (::select(max + 1, &fds, nullptr, nullptr, nullptr) == -1) {
    perror("cannot select()");
    throw;
  }
}

bool FileDescriptor::Select::ready(const FileDescriptor &fd) const {
  return FD_ISSET(fd.fd, &fds);
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

ssize_t FileDescriptor::forward(FileDescriptor &to) {
  char b[1024];

  const auto n = read(fd, b, sizeof(b));

  switch (n) {
  case -1:
    perror("cannot read()");
    throw;
  case 0:
    break;
  default:
    to.write({b, static_cast<size_t>(n)});
  }

  return n;
}

FileDescriptor::operator bool() const { return select.ready(*this); }

FileDescriptor::Select FileDescriptor::select;

FileDescriptor StdIn{STDIN_FILENO};
FileDescriptor StdOut{STDOUT_FILENO};
FileDescriptor StdErr{STDERR_FILENO};
