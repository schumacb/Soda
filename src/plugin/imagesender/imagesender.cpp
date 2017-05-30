#include "imagesender.hpp"

#include <QJsonObject>

// TODO:Remove
#include <opencv2/highgui.hpp>

#include "exception.hpp"
#include "sodaconfig.hpp"

namespace soda {
namespace plugin {
using namespace pluginapi;
namespace imagesender {

ImageSender::ImageSender(QObject *t_parent) : QObject(t_parent) {}

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
    cv::namedWindow("Raw Frame");
  }

  cv::imshow("Raw Frame", t_frame);
}

const QJsonObject &ImageSender::getConfiguration() const {
  // TODO: implement
  throw NotYetImplemented();
}

const QString ImageSender::getID() const { return m_id; }

Plugin *ImageSender::getPlugin() const { return m_plugin; }

using namespace pluginapi;
ImageSenderPlugin::ImageSenderPlugin(QObject *parent) : QObject(parent) {}

const QString ImageSenderPlugin::getName() const { return "ImageSender"; }

const QString ImageSenderPlugin::getDescription() const {
  // TODO: Describe Plugin.
  return "DESCRIPTION";
}

const QString ImageSenderPlugin::getAuthor() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString ImageSenderPlugin::getMaintainer() const {
  return Soda_AUTHOR_SCHUMACB;
}

const QString ImageSenderPlugin::getURL() const { return Soda_URL; }

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
