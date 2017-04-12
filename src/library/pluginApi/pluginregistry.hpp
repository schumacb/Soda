#ifndef PLUGINREGISTRY_HPP
#define PLUGINREGISTRY_HPP

#include <vector>

#include "plugininterface.hpp"

class PluginRegistry {
public:
  virtual ~PluginRegistry() {}

  virtual void registerPlugin(PluginInterface &t_plugin) = 0;

  virtual PluginInterface *findPlugin(const std::string t_pid,
                                      const Version t_version) = 0;
};

#endif // PLUGINREGISTRY_HPP
