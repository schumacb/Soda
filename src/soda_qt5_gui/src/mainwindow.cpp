#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <opencv2/opencv.hpp>

#include "imageview.h"

namespace soda {

// TODO: move somewhere else
static QImage cv_mat_to_q_image(cv::Mat& mat, QImage::Format image_format)
{
    return QImage(static_cast<uchar*>(mat.data), mat.cols, mat.rows, image_format);
}

static QImage cv_mat_to_q_image(cv::Mat& cvImg)
{
    // TODO: determine format from mat
    return cv_mat_to_q_image(cvImg, QImage::Format_RGB888);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow), _scene(new QGraphicsScene())
{
    _ui->setupUi(this);

    _ui->centralwidget
}

MainWindow::~MainWindow()
{
    delete _ui;
}

} // namespace soda
