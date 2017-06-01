#pragma once

#include <QCameraInfo>
#include <QtCore/qglobal.h>
#include <QtWidgets>

#include <nodes/NodeData>
#include <nodes/NodeModel>

namespace soda {
namespace plugin {
namespace corenodes {

class FrameGrabberWidget;

class FrameGrabberModel : public QtNodes::SimpleNodeModel {
  Q_OBJECT
private:
  FrameGrabberWidget *m_widget;

  int m_device{-1};
  QString m_url{""};
  int m_availableDevices{QCameraInfo::availableCameras().size()};

public:
  FrameGrabberModel();
  virtual ~FrameGrabberModel();

  // No copy or assignment
  FrameGrabberModel(const FrameGrabberModel &other) = delete;
  FrameGrabberModel operator=(const FrameGrabberModel &other) = delete;

  // NodeDataModel interface
  QString name() const override;
  QWidget *embeddedWidget() override;
  std::unique_ptr<QtNodes::NodeDataModel> clone() const override;
  unsigned int nPorts(QtNodes::PortType portType) const override;
  QtNodes::NodeDataType dataType(QtNodes::PortType portType,
                                 QtNodes::PortIndex portIndex) const override;
  // Serializable interface
public:
  QJsonObject save() const override;
  void restore(const QJsonObject &object) override;

  // getters
  int getDevice() const;
  QString getUrl() const;
public slots:
  void setUrl(const QString &t_text);
  void setDevice(const int t_id);
signals:
  void deviceChanged(int id);
  void urlChanged(QString url);
};

} // namespace corenodes
} // namespace plugin
} // namespace soda
