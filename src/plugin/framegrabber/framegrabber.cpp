#include "framegrabber.hpp"

#include <memory>

#include <QJsonObject>

#include "exception.hpp"

namespace soda {
namespace plugin {
namespace framegrabber {

FrameGrabber::FrameGrabber(QString id, QObject *t_parent)
    : QObject(t_parent), m_id{id} {}

void FrameGrabber::setConfiguration(const QJsonObject &t_config) {
  if (!t_config.contains("sourceType")) {
    throw AlgorithmNode::InvalidConfiguration();
  }
  SourceType sourceType = SourceType(t_config["sourceType"].toDouble());
  switch (sourceType) {
  case SourceType::Device:
    break;
  case SourceType::Stream:
    break;
  }
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
      open = m_capture.open(0);
    } while (!open);
  }
}

using namespace pluginapi;

FrameGrabberPlugin::FrameGrabberPlugin(QObject *parent) : QObject(parent) {}

void FrameGrabberPlugin::onLoad(PluginRegistry &t_registry) {
  t_registry.registerAlgorithm(m_frameGrabberFactory);
}

void FrameGrabberPlugin::onUnload(PluginRegistry &t_registry) {
  // TODO: implement
  Q_UNUSED(t_registry)
}

std::unique_ptr<AlgorithmNode>
FrameGrabberFactory::createAlgorithm(const QString t_id,
                                     QObject *t_parent) const {
  return std::make_unique<FrameGrabber>(t_id, t_parent);
}

AlgorithmType FrameGrabberFactory::getAlgorithmType() const {
  return m_framegrabber_type;
}

} // namespace framegrabber
} // namespace plugin
} // namespace soda
