#ifndef PLUGININTERFACE_HPP
#define PLUGININTERFACE_HPP

#include <string>

#include <QObject>
#include <QtPlugin>

#include "pluginapiconfig.hpp"
#include "version.hpp"

class Plugin {

protected:
  Plugin() {}

  constexpr static Version interface_version{PluginApi_VERSION_MAJOR,
                                             PluginApi_VERSION_MINOR,
                                             PluginApi_VERSION_PATCH};

public:
  // no copy operations
  Plugin(const Plugin &) = delete;
  Plugin &operator=(const Plugin &) = delete;

  // no move operations
  Plugin(const Plugin &&) = delete;
  Plugin &operator=(const Plugin &&) = delete;

  inline virtual ~Plugin() {}

  inline static constexpr Version getInterfaceVersion() {
    return interface_version;
  }

  virtual const std::string getName() const = 0;
  virtual const std::string getDescription() const = 0;
  virtual const std::string getPid() const = 0;
  virtual const Version getVersion() const = 0;

  virtual void onLoad() = 0;
  virtual void onUnload() = 0;

  template <typename Feature> Feature getFeature(std::string fid);
};

#define PluginInterface_IID "de.hochschule-trier.soda.PluginInterface"

Q_DECLARE_INTERFACE(Plugin, PluginInterface_IID)

#endif // PLUGININTERFACE_HPP
