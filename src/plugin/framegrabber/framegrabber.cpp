#include "framegrabber.hpp"

#include <memory>

#include <QJsonObject>

#include "exception.hpp"

namespace soda {
namespace plugin {
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

QString FrameGrabber::getID() { return m_id; }

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

using namespace pluginapi;

FrameGrabberPlugin::FrameGrabberPlugin(QObject *parent) : QObject(parent) {}

void FrameGrabberPlugin::onLoad(PluginRegistry &t_registry) {
  t_registry.registerAlgorithm(m_frame_grabber_factory);
}

void FrameGrabberPlugin::onUnload(PluginRegistry &t_registry) {
  // TODO: implement
  Q_UNUSED(t_registry)
}

AlgorithmNode *FrameGrabberFactory::createAlgorithm(QObject *t_parent) const {
  return new FrameGrabber(t_parent);
}

AlgorithmType FrameGrabberFactory::getAlgorithmType() const {
  return m_framegrabber_type;
}

} // namespace framegrabber
} // namespace plugin
} // namespace soda
