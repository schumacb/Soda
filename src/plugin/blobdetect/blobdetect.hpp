#ifndef FRAMEGRABBER_HPP
#define FRAMEGRABBER_HPP

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>

#include "plugininterface.hpp"

#include "pluginconfig.hpp"

#define BlobDetectPluginID "de.hochschule-trier.soda.plugin.blobdetect"

namespace Soda {

namespace Plugin {

namespace BlobDetect {

class BlobDetect : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID BlobDetectPluginID FILE "blobdetect.json")
    Q_INTERFACES(PluginInterface)
protected:
    const std::string PID = BlobDetectPluginID;
    static constexpr Version VERSION = {PLUGIN_VERSION_MAJOR,PLUGIN_VERSION_MINOR,PLUGIN_VERSION_PATCH};
    const std::string NAME = "BlobDetect";
    const std::string DESCRIPTION = "TODO"; // TODO: Describe Plugin.

public:
    BlobDetect(QObject* parent=0);

    const std::string getPid() const { return PID; }
    const Version getVersion() const { return BlobDetect::VERSION; }
    const std::string getName() const { return NAME; }
    const std::string getDescription() const { return DESCRIPTION; }

    void onLoad();
    void onUnload();

};

} // namespace BlobDetect

} // namespace Plugin

} // namespace Soda

#endif // FRAMEGRABBER_HPP
