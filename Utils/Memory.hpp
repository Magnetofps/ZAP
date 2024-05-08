#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sys/uio.h>
#include <cmath>
#include "Config.hpp"

namespace Memory {
  inline pid_t PID = 0;

  inline pid_t GetPID() {
    if (PID > 0)
      return PID;

    for (const auto &Entry: std::filesystem::directory_iterator("/proc")) {
      if (!Entry.is_directory())
        continue;

      std::ifstream CommandFile(std::string(Entry.path()) + "/cmdline");
      std::string CommandLine;
      std::getline(CommandFile, CommandLine);

      if (CommandLine.find("r5apex.exe") != std::string::npos) {
        PID = std::stoi(Entry.path().filename());
        break;
      }
    }
    return PID;
  }

  inline bool IsValidPointer(const long Pointer) { return Pointer > 0x00010000 && Pointer < 0x7FFFFFFEFFFF; }

  inline bool Access(const bool isWrite, const long address, void *pBuff, const size_t size) {
    if (size == 0)
      return false;

    void *pAddress = reinterpret_cast<void *>(address);
    const pid_t pid = GetPID();
    iovec iovLocalAddressSpace[1]{nullptr};
    iovec iovRemoteAddressSpace[1]{nullptr};
    iovLocalAddressSpace[0].iov_base = pBuff; // buffer for storing data
    iovLocalAddressSpace[0].iov_len = size;   // ^ size
    iovRemoteAddressSpace[0].iov_base = pAddress; // data origin/target
    iovRemoteAddressSpace[0].iov_len = size;      // ^ size

    if (isWrite) {
      if (const ssize_t sSize = process_vm_writev(pid, iovLocalAddressSpace, 1, iovRemoteAddressSpace, 1, 0); sSize == static_cast<ssize_t>(size))
        return true;
    } else {
      if (const ssize_t sSize = process_vm_readv(pid, iovLocalAddressSpace, 1, iovRemoteAddressSpace, 1, 0); sSize == static_cast<ssize_t>(size))
        return true;
    }

    return false;
  }

  template<class T>
  T Read(const long Address) {
    T buffer;
    if (const bool success = Access(false, Address, &buffer, sizeof(T)); !success)
      PID = 0;

    return buffer;
  }

  template<class T>
  void Write(const long Address, T Value) {
    if (const bool success = Access(true, Address, &Value, sizeof(T)); !success)
      PID = 0;
  }

  inline std::string ReadString(const long address, const int size = sizeof(std::string)) {
    char buffer[size] = {};
    Access(false, address, &buffer, size);
    return {buffer};
  }
}
