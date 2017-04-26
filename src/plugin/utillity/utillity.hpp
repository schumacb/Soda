#ifndef UTILLITY_HPP
#define UTILLITY_HPP

#include <QObject>
#include <QtPlugin>

#include <opencv2/opencv.hpp>

#include "plugin.hpp"

#include "pluginconfig.hpp"

// TODO: begin remove
#include "framegrabber.h"
#include "imagerenderer.hpp"
// TODO: end remove

#define UtillityPluginID "de.hochschule-trier.soda.plugin.utillity"

namespace soda {

namespace plugin {

namespace utillity {

class Utillity : public QObject, public Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID UtillityPluginID FILE "utillity.json")
  Q_INTERFACES(Plugin)
protected:
  const std::string PID = UtillityPluginID;
  static constexpr Version VERSION = {
      PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_PATCH};
  const std::string NAME = "Utillity";
  const std::string DESCRIPTION = "TODO"; // TODO: Describe Plugin.

  // TODO: begin remove
  FrameGrabber m_frameGrabber{};
  ImageRenderer m_imageRenderer{};

public:
  FrameGrabber &getFrameGrabber() { return m_frameGrabber; }
  ImageRenderer &getImageRenderer() { return m_imageRenderer; }
  // TODO: end remove
  Utillity(QObject *parent = 0);
  ~Utillity() {}

  const std::string getPid() const override { return PID; }
  const Version getVersion() const override { return Utillity::VERSION; }
  const std::string getName() const override { return NAME; }
  const std::string getDescription() const override { return DESCRIPTION; }

  void onLoad() override;
  void onUnload() override;
};

} // namespace Utillity

} // namespace Plugin

} // namespace Soda

#endif // UTILLITY_HPP
