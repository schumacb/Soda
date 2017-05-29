#pragma once

#include <QtCore/qglobal.h>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class ImagePreviewDataModel : public QtNodes::NodeDataModel {
private:
  QLabel *m_label;

public:
  ImagePreviewDataModel();
  virtual ~ImagePreviewDataModel();

  // No copy or assignment

  ImagePreviewDataModel(const ImagePreviewDataModel &other) = delete;
  ImagePreviewDataModel operator=(const ImagePreviewDataModel &other) = delete;

  // NodeDataModel interface
public:
  QString caption() const;
  QString name() const;
  std::unique_ptr<QtNodes::NodeDataModel> clone() const;
  unsigned int nPorts(QtNodes::PortType portType) const;
  QtNodes::NodeDataType dataType(QtNodes::PortType portType,
                                 QtNodes::PortIndex portIndex) const;
  void setInData(std::shared_ptr<QtNodes::NodeData> nodeData,
                 QtNodes::PortIndex port);
  std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex port);
  QWidget *embeddedWidget();

  // Serializable interface
public:
  QJsonObject save() const;
  void restore(const QJsonObject &);
};
