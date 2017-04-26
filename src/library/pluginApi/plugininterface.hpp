#ifndef PLUGININTERFACE_HPP
#define PLUGININTERFACE_HPP

#include <string>

#include <QObject>
#include <QtPlugin>

#include "pluginapiconfig.hpp"
#include "version.hpp"

class PluginInterface {

protected:
  PluginInterface() {}

  constexpr static Version interface_version{PluginApi_VERSION_MAJOR,
                                             PluginApi_VERSION_MINOR,
                                             PluginApi_VERSION_PATCH};

public:
  // no copy operations
  PluginInterface(const PluginInterface &) = delete;
  PluginInterface &operator=(const PluginInterface &) = delete;

  // no move operations
  PluginInterface(const PluginInterface &&) = delete;
  PluginInterface &operator=(const PluginInterface &&) = delete;

  inline virtual ~PluginInterface() {}

  inline static constexpr Version getInterfaceVersion() {
    return interface_version;
  }

  virtual const std::string getName() const = 0;
  virtual const std::string getDescription() const = 0;
  virtual const std::string getPid() const = 0;
  virtual const Version getVersion() const = 0;

  virtual void onLoad() = 0;
  virtual void onUnload() = 0;
};

#define PluginInterface_IID "de.hochschule-trier.soda.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_IID)

#endif // PLUGININTERFACE_HPP
