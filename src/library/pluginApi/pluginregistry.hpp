#ifndef PLUGINREGISTRY_HPP
#define PLUGINREGISTRY_HPP

#include <vector>

#include "plugininterface.hpp"

class PluginRegistry {
public:
    virtual void registerPlugin(PluginInterface *p) = 0;
    virtual std::vector<PluginInterface*> findPluginByName(std::string name) = 0;
    virtual std::vector<PluginInterface*> findPluginByName(std::string name, Version version, bool exactVersion=false) = 0;
    virtual PluginInterface *finPlugin(std::string pid, Version version) = 0;

};

#endif // PLUGINREGISTRY_HPP

