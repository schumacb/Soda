#ifndef UTILLITY_HPP
#define UTILLITY_HPP

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>

#include "plugininterface.hpp"

#include "pluginconfig.hpp"

#define UtillityPluginID "de.hochschule-trier.soda.plugin.utillity"

namespace Soda {

namespace Plugin {

namespace Utillity {

class Utillity : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID UtillityPluginID FILE "utillity.json")
    Q_INTERFACES(PluginInterface)
protected:
    const std::string PID = UtillityPluginID;
    static constexpr Version VERSION = {PLUGIN_VERSION_MAJOR,PLUGIN_VERSION_MINOR,PLUGIN_VERSION_PATCH};
    const std::string NAME = "Utillity";
    const std::string DESCRIPTION = "TODO"; // TODO: Describe Plugin.

public:
    Utillity(QObject* parent=0);

    const std::string getPid() const { return PID; }
    const Version getVersion() const { return Utillity::VERSION; }
    const std::string getName() const { return NAME; }
    const std::string getDescription() const { return DESCRIPTION; }

    void onLoad();
    void onUnload();

};

} // namespace Utillity

} // namespace Plugin

} // namespace Soda

#endif // UTILLITY_HPP
