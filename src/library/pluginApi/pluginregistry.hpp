#pragma once

#include <string>

namespace soda {
namespace pluginapi {

// forward declarations
class Plugin;
class Version;
class AlgorithmFactory;

class PluginRegistry {

protected:
  PluginRegistry() {}

public:
  // no copy operations
  PluginRegistry(const PluginRegistry &) = delete;
  PluginRegistry &operator=(const PluginRegistry &) = delete;

  // no move operations
  PluginRegistry(const PluginRegistry &&) = delete;
  PluginRegistry &operator=(const PluginRegistry &&) = delete;

  virtual ~PluginRegistry() {}

  virtual void registerPlugin(Plugin &t_plugin) = 0;
  virtual void registerAlgorithm(AlgorithmFactory &factory) = 0;

  virtual Plugin *findPlugin(const std::string &t_pid,
                             const Version &t_version) = 0;
};

} // pluginapi
} // soda
