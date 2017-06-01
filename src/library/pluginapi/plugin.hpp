#pragma once

#include <memory>
#include <string>

#include <QObject>
#include <QtPlugin>

#include "pluginapiconfig.hpp"
#include "version.hpp"

namespace soda {
namespace pluginapi {

class PluginRegistry;

class Plugin {

public:
  virtual ~Plugin() = default;

  inline static constexpr Version getInterfaceVersion() {
    return Version{PluginApi_VERSION_MAJOR, PluginApi_VERSION_MINOR,
                   PluginApi_VERSION_PATCH};
  }

  virtual const QString getName() const = 0;
  virtual const QString getDescription() const = 0;
  virtual const QString getAuthor() const = 0;
  virtual const QString getMaintainer() const = 0;
  virtual const QString getURL() const = 0;
  virtual const std::string getID() const = 0;
  virtual const Version getVersion() const = 0;

  virtual void onLoad(PluginRegistry &registry) = 0;
  virtual void onUnload(PluginRegistry &registry) = 0;
};

} // pluginapi
} // soda

#define Plugin_IID "de.hochschule-trier.soda.pluginapi.plugin"
Q_DECLARE_INTERFACE(soda::pluginapi::Plugin, Plugin_IID)
