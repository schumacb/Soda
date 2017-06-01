#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
QT_END_NAMESPACE

namespace Ui {
class FrameGrabberWidget;
}

namespace soda {
namespace plugin {
namespace corenodes {

class FrameGrabberWidget : public QWidget {
  Q_OBJECT

private:
  Ui::FrameGrabberWidget *ui{nullptr};
  QComboBox *m_device_selector{nullptr};
  QComboBox *m_url_editor{nullptr};

protected:
  void changeEvent(QEvent *e);

public:
  explicit FrameGrabberWidget(QWidget *parent = 0);
  ~FrameGrabberWidget();

  FrameGrabberWidget(const FrameGrabberWidget &other) = delete;
  const FrameGrabberWidget &operator=(const FrameGrabberWidget &other) = delete;

public slots:
  void on_device_selector_currentIndexChanged(const int &index);
  void on_url_editor_currentTextChanged(const QString &url);
  void on_url_editor_currentIndexChanged(const QString &url);
  void setDevice(const int &index);
  void setUrl(const QString &url);
signals:
  void deviceChanged(const int &index);
  void urlChanged(const QString &url);
};

} // namespace corenodes
} // namespace plugin
} // namespace soda
