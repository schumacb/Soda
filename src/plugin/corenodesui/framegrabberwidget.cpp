#include "framegrabberwidget.hpp"
#include "ui_framegrabberwidget.h"

#include <QCameraInfo>

using namespace soda::plugin::corenodes;

FrameGrabberWidget::FrameGrabberWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::FrameGrabberWidget) {
  ui->setupUi(this);
  m_url_editor = this->findChild<QComboBox *>("url_editor");
  m_device_selector = this->findChild<QComboBox *>("device_selector");
  Q_ASSERT(m_url_editor);
  Q_ASSERT(m_device_selector);

  QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
  for (const QCameraInfo &cameraInfo : cameras) {
    m_device_selector->addItem(cameraInfo.description() + " (" +
                               cameraInfo.deviceName() + ")");
  }
}

FrameGrabberWidget::~FrameGrabberWidget() { delete ui; }

void FrameGrabberWidget::changeEvent(QEvent *e) {
  QWidget::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void FrameGrabberWidget::on_device_selector_currentIndexChanged(
    const int &t_index) {
  emit deviceChanged(t_index - 1);
  setDevice(t_index);
}

void FrameGrabberWidget::on_url_editor_currentTextChanged(
    const QString &t_url) {
  emit urlChanged(t_url);
  setUrl(t_url);
}

void FrameGrabberWidget::on_url_editor_currentIndexChanged(
    const QString &t_url) {
  emit urlChanged(t_url);
  setUrl(t_url);
}

void FrameGrabberWidget::setDevice(const int &t_index) {
  m_url_editor->setEnabled(t_index == 0);
}

void FrameGrabberWidget::setUrl(const QString &t_url) {
  m_device_selector->setEnabled(t_url == "");
}
