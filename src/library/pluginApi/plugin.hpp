#pragma once

#include <memory>
#include <string>

#include <QObject>
#include <QtPlugin>

#include "algorithm.hpp"
#include "pluginapiconfig.hpp"
#include "pluginregistry.hpp"
#include "version.hpp"

namespace soda {
namespace pluginapi {

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
    return Version{PluginApi_VERSION_MAJOR, PluginApi_VERSION_MINOR,
                   PluginApi_VERSION_PATCH};
  }

  virtual const QString getName() const = 0;
  virtual const QString getDescription() const = 0;
  virtual const std::string getPid() const = 0;
  virtual const Version getVersion() const = 0;

  virtual void onLoad(PluginRegistry &registry) = 0;
  virtual void onUnload(PluginRegistry &registry) = 0;
};

} // pluginapi
} // soda

#define PluginInterface_IID "de.hochschule-trier.soda.PluginInterface"

Q_DECLARE_INTERFACE(soda::pluginapi::Plugin, PluginInterface_IID)
