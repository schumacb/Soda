#pragma once

#include <string>
#include "version.hpp"

class Plugin {

protected:
  Plugin() {}

public:
  // no copy operations
  Plugin(const Plugin &) = delete;
  Plugin &operator=(const Plugin &) = delete;

  // no move operations
  Plugin(const Plugin &&) = delete;
  Plugin &operator=(const Plugin &&) = delete;

  inline virtual ~Plugin() {}

  inline static constexpr Version getInterfaceVersion() {
    return Version{0, 3, 0};
  }

  virtual const std::string getName() const = 0;
  virtual const std::string getDescription() const = 0;
  virtual const std::string getPid() const = 0;
  virtual const Version getVersion() const = 0;

  virtual void onLoad() = 0;
  virtual void onUnload() = 0;
};
