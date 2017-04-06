#ifndef PLUGININTERFACE_HPP
#define PLUGININTERFACE_HPP

#include <string>

#include <QtPlugin>

#include "version.hpp"
#include "pluginapiconfig.hpp"

class PluginInterface {
private:
    constexpr static Version INTERFACE_VERSION = { PluginApi_VERSION_MAJOR,
                                                   PluginApi_VERSION_MINOR,
                                                   PluginApi_VERSION_PATCH};
public:
    const Version getInterfaceVersion() const { return INTERFACE_VERSION; }

    virtual const std::string getName() const = 0;
    virtual const std::string getDescription() const  = 0;
    virtual const std::string getPid() const = 0;
    virtual const Version getVersion() const = 0;

    virtual void onLoad() = 0;
    virtual void onUnload() = 0;
};

#define PluginInterface_IID "de.hochschule-trier.soda.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_IID)

#endif // PLUGININTERFACE_HPP
