#include "framegrabber.hpp"

#include <memory>

#include <QJsonObject>

#include "exception.hpp"
#include "plugin.hpp"
#include "sodaconfig.hpp"

namespace soda {
namespace plugin {

using namespace pluginapi;

namespace framegrabber {

FrameGrabber::FrameGrabber(QObject *t_parent) : QObject(t_parent) {}

void FrameGrabber::setConfiguration(const QJsonObject &t_config) {
  if (!t_config.contains("device")) {
    throw AlgorithmNode::InvalidConfiguration();
  }
  if (!t_config.contains("url")) {
    throw AlgorithmNode::InvalidConfiguration();
  }
  m_device = t_config["device"].toInt();
  m_url = t_config["url"].toString().toStdString();
}

const QJsonObject &FrameGrabber::getConfiguration() const {
  // TODO: implement
  throw NotYetImplemented();
}

const QString FrameGrabber::getID() const { return m_id; }

Plugin *FrameGrabber::getPlugin() const { return m_plugin; }

void FrameGrabber::run() {

  if (m_capture.isOpened()) {
    cv::Mat frame;
    m_capture >> frame;
    emit signal_imageReady(frame);

  } else {
    bool open;
    do {
      if (m_device == -1) { // use stream
        open = m_capture.open(m_url);
      } else { // use device
        open = m_capture.open(m_device);
      }
    } while (!open);
  }
}

const char *FrameGrabber::getSignal(int t_index) const {
  if (t_index == 0) {
    return SIGNAL(signal_imageReady(cv::Mat));
  }
  return "";
}

const char *FrameGrabber::getSlot(int t_index) const {
  Q_UNUSED(t_index)
  return "";
}

using namespace pluginapi;

FrameGrabberPlugin::FrameGrabberPlugin(QObject *parent) : QObject(parent) {}

void FrameGrabberPlugin::onLoad(PluginRegistry &t_registry) {
  t_registry.registerAlgorithm(m_frame_grabber_factory);
}

void FrameGrabberPlugin::onUnload(PluginRegistry &t_registry) {
  // TODO: implement
  Q_UNUSED(t_registry)
}

const QString FrameGrabberPlugin::getAuthor() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString FrameGrabberPlugin::getMaintainer() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString FrameGrabberPlugin::getURL() const { return Soda_URL; }

AlgorithmNode *FrameGrabberFactory::createAlgorithm(QObject *t_parent) const {
  return new FrameGrabber(t_parent);
}

AlgorithmType FrameGrabberFactory::getAlgorithmType() const {
  return m_framegrabber_type;
}

} // namespace framegrabber
} // namespace plugin
} // namespace soda
