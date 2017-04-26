#ifndef PLUGINREGISTRY_HPP
#define PLUGINREGISTRY_HPP

#include <vector>

#include "plugininterface.hpp"

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

  virtual void registerPlugin(PluginInterface &t_plugin) = 0;

  virtual PluginInterface *findPlugin(const std::string t_pid,
                                      const Version t_version) = 0;
};

#endif // PLUGINREGISTRY_HPP
