#include "framegrabbermodel.hpp"

#include <QCameraInfo>
#include <QComboBox>

#include "framegrabberwidget.hpp"
#include "ui_framegrabberwidget.h"

using namespace soda::plugin::corenodes;

FrameGrabberModel::FrameGrabberModel() : m_widget{new FrameGrabberWidget()} {

  connect(m_widget, SIGNAL(deviceChanged(int)), this, SLOT(setDevice(int)));
  connect(m_widget, SIGNAL(urlChanged(QString)), this, SLOT(setUrl(QString)));

  connect(this, SIGNAL(deviceChanged(int)), this, SLOT(setDevice(int)));
  connect(this, SIGNAL(urlChanged(QString)), this, SLOT(setUrl(QString)));
}

FrameGrabberModel::~FrameGrabberModel() {
  // TODO: delete m_widget;
}

QString FrameGrabberModel::name() const {
  return QStringLiteral("FrameGrabber");
}

std::unique_ptr<QtNodes::NodeDataModel> FrameGrabberModel::clone() const {
  return std::make_unique<FrameGrabberModel>();
}

unsigned int FrameGrabberModel::nPorts(QtNodes::PortType t_portType) const {

  switch (t_portType) {
  case QtNodes::PortType::Out:
    return 1;
  case QtNodes::PortType::In:
  case QtNodes::PortType::None:
    break;
  }
  return 0;
}

QtNodes::NodeDataType FrameGrabberModel::dataType(QtNodes::PortType,
                                                  QtNodes::PortIndex) const {
  return QtNodes::NodeDataType{"cv::Mat", "Mat"};
}

QWidget *FrameGrabberModel::embeddedWidget() { return m_widget; }

QString FrameGrabberModel::getUrl() const { return m_url; }

int FrameGrabberModel::getDevice() const { return m_device; }

QJsonObject FrameGrabberModel::save() const {

  QJsonObject object{
      {"pid", "de.hochschule-trier.soda.plugin.node.framegrabber"},
      {"device", m_device},
      {"availableDevices", m_availableDevices},
      {"url", m_url}};
  return object;
}

void FrameGrabberModel::restore(const QJsonObject &t_object) {
  m_device = static_cast<short>(t_object["device"].toInt(-1));
  m_availableDevices =
      static_cast<short>(t_object["availableDevices"].toInt(-1));
  m_url = t_object["url"].toString("");
}

void FrameGrabberModel::setUrl(const QString &t_url) {
  if (m_url == t_url) {
    return;
  }
  m_url = t_url;
  emit urlChanged(t_url);
}

void FrameGrabberModel::setDevice(const int t_id) {
  if (m_device == t_id) {
    return;
  }
  m_device = t_id;
  emit deviceChanged(t_id);
}
