#include "imagesender.hpp"

#include <QJsonObject>

// TODO:Remove
#include <opencv2/highgui.hpp>

#include "exception.hpp"
#include "sodaconfig.hpp"

using namespace soda;
using namespace soda::pluginapi;
using namespace soda::plugin::corenodes;

const NodeType ImageSender::TYPE = NodeType(
    "de.hochschule-trier.soda.plugin.node.imagesender", "ImageSender", "");
// TODO: add Description

int ImageSender::instance_count = 0;

ImageSender::ImageSender(QObject *t_parent) : QObject(t_parent) {
  m_window_name = "ImagePreview " + std::to_string(++instance_count);
}

void ImageSender::setConfiguration(const QJsonObject &t_config) {
  // TODO: implement
  Q_UNUSED(t_config)
}

const char *ImageSender::getSignal(int t_index) const {
  Q_UNUSED(t_index)
  return "";
}

const char *ImageSender::getSlot(int t_index) const {
  if (t_index == 0) {
    return SLOT(slot_process(cv::Mat));
  }
  return "";
}

void ImageSender::run() {}

void ImageSender::slot_process(cv::Mat t_frame) {
  static bool initialized = false;
  if (!initialized) {

    cv::namedWindow(m_window_name);
  }

  cv::imshow(m_window_name, t_frame);
}

const QJsonObject ImageSender::getConfiguration() const {
  // TODO: implement
  throw NotYetImplemented();
}

const NodeType &ImageSender::getType() const { return ImageSender::TYPE; }

ImageSenderFactory::ImageSenderFactory(QObject *t_parent) : QObject(t_parent) {}

Node *ImageSenderFactory::createNode(QObject *t_parent) const {
  return new ImageSender(t_parent);
}

const NodeType &ImageSenderFactory::getType() const {
  return ImageSender::TYPE;
}
