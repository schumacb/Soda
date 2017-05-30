#include "framegrabberdatamodel.hpp"

#include <QCameraInfo>

FrameGrabberDataModel::FrameGrabberDataModel() {

  //  QComboBox *m_urlEditor{new QComboBox(m_widget)};
  //  QComboBox *m_deviceSelector{new QComboBox(m_widget)};
  //  void set_m_url(const QString &t_text);
  //  void set_m_device(const int t_id);

  connect(m_urlEditor, SIGNAL(currentTextChanged(const QString &)), this,
          SLOT(set_m_url(const QString &)));
  connect(m_urlEditor, SIGNAL(currentIndexChanged(const QString &)), this,
          SLOT(set_m_url(const QString &)));
  connect(m_deviceSelector, SIGNAL(currentIndexChanged(const int)), this,
          SLOT(set_m_device(int)));

  m_widget->setStyleSheet("background-color:white;");
  m_urlEditor->setStyleSheet("selection-color: blue;");
  m_deviceSelector->setStyleSheet("selection-color: blue;");
  auto *layout = new QFormLayout(m_widget);

  QStringList recentConnections;
  recentConnections << "localhost";

  auto *connectionCompleter = new QCompleter(recentConnections, this);
  connectionCompleter->setCaseSensitivity(Qt::CaseInsensitive);
  m_urlEditor->setEditable(true);
  m_urlEditor->setCompleter(connectionCompleter);

  layout->addRow("Device:", m_deviceSelector);
  layout->addRow("URL:", m_urlEditor);
  m_widget->setLayout(layout);

  m_deviceSelector->addItem("None (use URL)");

  QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
  for (const QCameraInfo &cameraInfo : cameras) {
    m_deviceSelector->addItem(cameraInfo.description() + " (" +
                              cameraInfo.deviceName() + ")");
  }
}

FrameGrabberDataModel::~FrameGrabberDataModel() { delete m_widget; }

QString FrameGrabberDataModel::caption() const {
  return QStringLiteral("FrameGrabber");
}

bool FrameGrabberDataModel::captionVisible() const { return false; }

QString FrameGrabberDataModel::name() const {
  return QStringLiteral("FrameGrabber");
}

std::unique_ptr<QtNodes::NodeDataModel> FrameGrabberDataModel::clone() const {
  return std::make_unique<FrameGrabberDataModel>();
}

unsigned int FrameGrabberDataModel::nPorts(QtNodes::PortType t_portType) const {

  switch (t_portType) {
  case QtNodes::PortType::Out:
    return 1;
  case QtNodes::PortType::In:
  case QtNodes::PortType::None:
    break;
  }
  return 0;
}

QtNodes::NodeDataType
    FrameGrabberDataModel::dataType(QtNodes::PortType,
                                    QtNodes::PortIndex) const {
  return QtNodes::NodeDataType{"cv::Mat", "Mat"};
}

void FrameGrabberDataModel::setInData(std::shared_ptr<QtNodes::NodeData>,
                                      QtNodes::PortIndex) {}

std::shared_ptr<QtNodes::NodeData>
    FrameGrabberDataModel::outData(QtNodes::PortIndex) {
  std::shared_ptr<QtNodes::NodeData> ptr;
  return ptr;
}

QWidget *FrameGrabberDataModel::embeddedWidget() { return m_widget; }

QJsonObject FrameGrabberDataModel::save() const {

  QJsonObject object{
      {"name", name()},
      {"pid", "de.hochschule-trier.soda.plugin.algorithm.framegrabber"},
      {"device", m_device},
      {"availableDevices", m_availableDevices},
      {"url", m_url}};
  return object;
}

void FrameGrabberDataModel::restore(const QJsonObject &t_object) {
  m_device = static_cast<short>(t_object["device"].toInt(-1));
  m_availableDevices =
      static_cast<short>(t_object["availableDevices"].toInt(-1));
  m_url = t_object["url"].toString("");
}

void FrameGrabberDataModel::set_m_url(const QString &t_text) {
  m_url = t_text;
  m_deviceSelector->setEnabled(m_url == "");
}

void FrameGrabberDataModel::set_m_device(const int t_id) {
  m_device = t_id - 1;
  m_urlEditor->setEnabled(m_device == -1);
}
