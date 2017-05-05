#pragma once

#include <QCameraInfo>
#include <QtCore/qglobal.h>
#include <QtWidgets>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

class FrameGrabberDataModel : public QtNodes::NodeDataModel {
  Q_OBJECT
public:
  FrameGrabberDataModel();
  virtual ~FrameGrabberDataModel();

  // NodeDataModel interface
  QString caption() const override;
  bool captionVisible() const override;
  QString name() const override;
  std::unique_ptr<QtNodes::NodeDataModel> clone() const override;
  unsigned int nPorts(QtNodes::PortType portType) const override;
  QtNodes::NodeDataType dataType(QtNodes::PortType portType,
                                 QtNodes::PortIndex portIndex) const override;
  void setInData(std::shared_ptr<QtNodes::NodeData>,
                 QtNodes::PortIndex) override;
  std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex) override;
  QWidget *embeddedWidget() override;

protected:
  QWidget *m_widget{new QWidget()};
  QComboBox *m_urlEditor{new QComboBox(m_widget)};
  QComboBox *m_deviceSelector{new QComboBox(m_widget)};

  int m_device{-1};
  int m_availableDevices{QCameraInfo::availableCameras().size()};
  QString m_url{""};

  // Serializable interface
public:
  QJsonObject save() const override;
  void restore(const QJsonObject &object) override;

public slots:
  void set_m_url(const QString &t_text);
  void set_m_device(const int t_id);
};
