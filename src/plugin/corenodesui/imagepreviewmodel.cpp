#include "imagepreviewmodel.hpp"

#include <QLabel>

using namespace soda::plugin::corenodes;

ImagePreviewModel::ImagePreviewModel() : m_label{new QLabel("No Input")} {}

ImagePreviewModel::~ImagePreviewModel() {
  // TODO: delete m_label;
}

QString ImagePreviewModel::name() const {
  return QStringLiteral("ImagePreview");
}

std::unique_ptr<QtNodes::NodeDataModel> ImagePreviewModel::clone() const {
  return std::make_unique<ImagePreviewModel>();
}

unsigned int ImagePreviewModel::nPorts(QtNodes::PortType t_port_type) const {
  switch (t_port_type) {
  case QtNodes::PortType::In:
    return 1;
  case QtNodes::PortType::Out:
  case QtNodes::PortType::None:
    break;
  }
  return 0;
}

QtNodes::NodeDataType
ImagePreviewModel::dataType(QtNodes::PortType t_portType,
                            QtNodes::PortIndex t_portIndex) const {
  Q_UNUSED(t_portType)
  Q_UNUSED(t_portIndex)
  return QtNodes::NodeDataType{"cv::Mat", "Mat"};
}

QWidget *ImagePreviewModel::embeddedWidget() { return m_label; }

QJsonObject ImagePreviewModel::save() const {
  QJsonObject object{
      {"pid", "de.hochschule-trier.soda.plugin.node.imagesender"}};
  return object;
}

void ImagePreviewModel::restore(const QJsonObject &) {}
