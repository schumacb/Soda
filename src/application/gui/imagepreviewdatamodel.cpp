#include "imagepreviewdatamodel.hpp"

#include <QLabel>

ImagePreviewDataModel::ImagePreviewDataModel()
    : m_label{new QLabel("No Input")} {}

ImagePreviewDataModel::~ImagePreviewDataModel() { delete m_label; }

QString ImagePreviewDataModel::caption() const {
  return QStringLiteral("ImagePreview");
}

QString ImagePreviewDataModel::name() const {
  return QStringLiteral("ImagePreview");
}

std::unique_ptr<QtNodes::NodeDataModel> ImagePreviewDataModel::clone() const {
  return std::make_unique<ImagePreviewDataModel>();
}

unsigned int
ImagePreviewDataModel::nPorts(QtNodes::PortType t_port_type) const {
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
ImagePreviewDataModel::dataType(QtNodes::PortType portType,
                                QtNodes::PortIndex portIndex) const {
  return QtNodes::NodeDataType{"cv::Mat", "Mat"};
}

void ImagePreviewDataModel::setInData(
    std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port) {}

std::shared_ptr<QtNodes::NodeData>
ImagePreviewDataModel::outData(QtNodes::PortIndex port) {
  std::shared_ptr<QtNodes::NodeData> ptr;
  return ptr;
}

QWidget *ImagePreviewDataModel::embeddedWidget() { return m_label; }

QJsonObject ImagePreviewDataModel::save() const {
  QJsonObject object{
      {"name", name()},
      {"pid", "de.hochschule-trier.soda.plugin.algorithm.imagesender"}};
  return object;
}

void ImagePreviewDataModel::restore(const QJsonObject &) {}
