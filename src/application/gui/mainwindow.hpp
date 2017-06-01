#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  MainWindow(const MainWindow &other) = delete;
  const MainWindow &operator=(const MainWindow &other) = delete;

protected:
  void changeEvent(QEvent *e);

private:
  Ui::MainWindow *ui;
};
