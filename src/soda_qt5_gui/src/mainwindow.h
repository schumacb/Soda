#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QGraphicsScene;

namespace soda {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    QGraphicsScene *_scene;
};

} // namespace soda
