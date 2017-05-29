#include "imagesender.hpp"

#include <QJsonObject>

// TODO:Remove
#include <opencv2/highgui.hpp>

#include "exception.hpp"

namespace soda {
namespace plugin {
namespace imagesender {

ImageSender::ImageSender(QObject *t_parent) : QObject(t_parent) {}

void ImageSender::setConfiguration(const QJsonObject &t_config) {
  // TODO: implement
  Q_UNUSED(t_config)
}

void ImageSender::run() {}

void ImageSender::slot_process(cv::Mat t_frame) {
  static bool initialized = false;
  if (!initialized) {
    cv::namedWindow("Raw Frame");
  }

  cv::imshow("Raw Frame", t_frame);
}

const QJsonObject &ImageSender::getConfiguration() const {
  // TODO: implement
  throw NotYetImplemented();
}

QString ImageSender::getID() { return m_id; }

using namespace pluginapi;
ImageSenderPlugin::ImageSenderPlugin(QObject *parent) : QObject(parent) {}

void ImageSenderPlugin::onLoad(PluginRegistry &t_registry) {
  t_registry.registerAlgorithm(m_image_sender_factory);
}

void ImageSenderPlugin::onUnload(PluginRegistry &t_registry) {
  // TODO: implement
  Q_UNUSED(t_registry)
}

AlgorithmNode *ImageSenderFactory::createAlgorithm(QObject *t_parent) const {
  return new ImageSender(t_parent);
}

AlgorithmType ImageSenderFactory::getAlgorithmType() const {
  return m_image_sender_type;
}

} // namespace imagesender
} // namespace plugin
} // namespace soda
