#pragma once

#include <memory>
#include <string>

#include <QtPlugin>

namespace QtNodes {
class DataModelRegistry;
}

namespace soda {
namespace pluginapi {

class Plugin;
class Version;
class NodeFactory;

class PluginRegistry {

public:
  virtual ~PluginRegistry() = default;

  virtual void registerPlugin(Plugin &t_plugin) = 0;
  virtual void registerNodeFactory(NodeFactory &factory) = 0;
  virtual QtNodes::DataModelRegistry *getDataModelRegistry() = 0;

  virtual Plugin *findPlugin(const std::string &t_pid,
                             const Version &t_version) = 0;
};

} // pluginapi
} // soda
