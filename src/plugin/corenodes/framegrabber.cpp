#include "framegrabber.hpp"

#include <memory>

#include <QJsonObject>

#include "exception.hpp"
#include "plugin.hpp"
#include "sodaconfig.hpp"

using namespace soda;
using namespace soda::pluginapi;
using namespace soda::plugin::corenodes;

const NodeType FrameGrabber::TYPE = NodeType(
    "de.hochschule-trier.soda.plugin.node.framegrabber", "FramGrabber", "");
// TODO: add Description

FrameGrabber::FrameGrabber(QObject *t_parent) : QObject(t_parent) {}

void FrameGrabber::setConfiguration(const QJsonObject &t_config) {
  if (!t_config.contains("device")) {
    throw InvalidConfiguration();
  }
  if (!t_config.contains("url")) {
    throw InvalidConfiguration();
  }
  m_device = t_config["device"].toInt();
  m_url = t_config["url"].toString().toStdString();
}

const QJsonObject FrameGrabber::getConfiguration() const {
  // TODO: implement
  throw NotYetImplemented();
}

const NodeType &FrameGrabber::getType() const { return FrameGrabber::TYPE; }

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

FrameGrabberFactory::FrameGrabberFactory(QObject *t_parent)
    : QObject{t_parent} {}

Node *FrameGrabberFactory::createNode(QObject *t_parent) const {
  return new FrameGrabber(t_parent);
}

const NodeType &FrameGrabberFactory::getType() const {
  return FrameGrabber::TYPE;
}
