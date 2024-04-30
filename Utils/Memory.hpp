#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <sys/uio.h>
#include <math.h>
#include "Config.hpp"
namespace fs = std::filesystem;

namespace Memory {
  inline pid_t PID = 0;

  inline pid_t GetPID() {
    if (PID > 0)
      return PID;

    for (const auto &Entry: fs::directory_iterator("/proc")) {
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

  inline bool Read(const long address, void *pBuff, const size_t size) {
    if (size == 0)
      return false;
    void *pAddress = reinterpret_cast<void *>(address);
    const pid_t pid = GetPID();
    struct iovec iovLocalAddressSpace[1]{nullptr};
    struct iovec iovRemoteAddressSpace[1]{nullptr};
    iovLocalAddressSpace[0].iov_base = pBuff; // Store data in this buffer
    iovLocalAddressSpace[0].iov_len = size; // which has this size.
    iovRemoteAddressSpace[0].iov_base = pAddress; // The data comes from here
    iovRemoteAddressSpace[0].iov_len = size; // and has this size.
    if (const ssize_t sSize = process_vm_readv(pid, iovLocalAddressSpace, 1, iovRemoteAddressSpace, 1, 0); sSize == static_cast<ssize_t>(size))
      return true;

    return false;
  }

  inline bool Write(const long address, void *pBuff, const size_t size) {
    if (size == 0)
      return false;
    void *pAddress = reinterpret_cast<void *>(address);
    const pid_t pid = GetPID();
    struct iovec iovLocalAddressSpace[1]{nullptr};
    struct iovec iovRemoteAddressSpace[1]{nullptr};
    iovLocalAddressSpace[0].iov_base = pBuff; // Store data in this buffer
    iovLocalAddressSpace[0].iov_len = size; // which has this size.
    iovRemoteAddressSpace[0].iov_base = pAddress; // The data will be writted here
    iovRemoteAddressSpace[0].iov_len = size; // and has this size.
    if (const ssize_t sSize = process_vm_writev(pid, iovLocalAddressSpace, 1, iovRemoteAddressSpace, 1, 0); sSize == static_cast<ssize_t>(size))
      return true;

    return false;
  }

  template<class T>
  T Read(const long Address) {
    T buffer;
    if (const bool success = Read(Address, &buffer, sizeof(T)); !success)
      PID = 0;

    return buffer;
  }

  template<class T>
  void Write(const long Address, T Value) {
    if (const bool success = Write(Address, &Value, sizeof(T)); !success)
      PID = 0;
  }

  inline std::string ReadString(const long address) {
    constexpr int size = sizeof(std::string);
    char buffer[size] = {};
    Read(address, &buffer, size);
    return {buffer};
  }

  inline std::string ReadString1(const long address) { //For Read Name + Read Level
    constexpr int size = sizeof(std::string);
    char buffer[size] = {};
    Read(address, &buffer, size);
    return {buffer};
  }

  inline std::string ReadLegend(const long address, const int size) {
    char buffer[size] = {};
    Read(address, &buffer, size);
    return {buffer};
  }

  inline std::string ReadPlayerName(const long address, const int size) {
    char buffer[size] = {};
    Read(address, &buffer, size);
    return {buffer};
  }

  inline std::string ConvertPointerToHexString(const long pointer) {
    std::stringstream stream;
    stream << "0x" << std::hex << pointer;
    return stream.str();
  }
}
