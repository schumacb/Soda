
#include <QCoreApplication>
#include <QDir>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>

#include <nodes/ConnectionStyle>
#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>
#include <nodes/NodeData>
#include <nodes/NodeStyle>

#include "framegrabber.hpp"
#include "framegrabberdatamodel.hpp"
#include "mainwindow.hpp"
#include "models.hpp"
#include "pluginmanager.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;

using namespace soda::plugin::framegrabber;
using namespace soda::pluginapi;
using namespace soda::pluginmanager;

static std::shared_ptr<DataModelRegistry> registerDataModels() {
  auto ret = std::make_shared<DataModelRegistry>();

  ret->registerModel<FrameGrabberDataModel>();
  ret->registerModel<ImageSourceModel>();
  ret->registerModel<ImageSinkModel>();

  return ret;
}

static void setStyle() {
  FlowViewStyle::setStyle(
      R"(
  {
    "FlowViewStyle": {
      "BackgroundColor": [240, 240, 245],
      "FineGridColor": [230, 230, 235],
      "CoarseGridColor": [220, 220, 225]
    }
  }
  )");

  NodeStyle::setNodeStyle(
      R"(
  {
    "NodeStyle": {
      "NormalBoundaryColor": "darkgray",
      "SelectedBoundaryColor": "deepskyblue",
      "GradientColor0": "white",
      "GradientColor1": "white",
      "GradientColor2": "white",
      "GradientColor3": "white",
      "ShadowColor": [200, 200, 200],
      "FontColor": [10, 10, 10],
      "FontColorFaded": [100, 100, 100],
      "ConnectionPointColor": "white",
      "PenWidth": 2.0,
      "HoveredPenWidth": 2.5,
      "ConnectionPointDiameter": 10.0,
      "Opacity": 1.0
    }
  }
  )");

  ConnectionStyle::setConnectionStyle(
      R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  }
  )");
}

int main(int argc, char **argv) {

  QApplication app(argc, argv);

  setStyle();

  MainWindow mainWidget;

  auto menuBar = new QMenuBar();
  auto saveAction = menuBar->addAction("Save..");
  auto loadAction = menuBar->addAction("Load..");

  QVBoxLayout *l = new QVBoxLayout(mainWidget.centralWidget());

  l->addWidget(menuBar);
  auto scene = new FlowScene(registerDataModels());
  l->addWidget(new FlowView(scene));
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  QObject::connect(saveAction, &QAction::triggered, scene, &FlowScene::save);

  QObject::connect(loadAction, &QAction::triggered, scene, &FlowScene::load);

  mainWidget.setWindowTitle("Soda - Simple Object Detection Application");
  mainWidget.resize(800, 600);
  mainWidget.showNormal();

  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/../lib");
  PluginManager pm;

  auto libPaths = app.libraryPaths();

  pm.loadPlugins(libPaths);

  Plugin *pi = pm.findPlugin("de.hochschule-trier.soda.plugin.utillity",
                             Version{0, 1, 0});
  if (pi) {
    FrameGrabberPlugin *ut = dynamic_cast<FrameGrabberPlugin *>(pi);
    // Utillity* ut = (Utillity*)pi;
    QObject *iso = dynamic_cast<QObject *>(&ut->getFrameGrabber());
    QObject *ipo = dynamic_cast<QObject *>(&ut->getImageRenderer());
    ImageSource *is = &ut->getFrameGrabber();

    QObject::connect(iso, SIGNAL(signal_imageReady(cv::Mat)), ipo,
                     SLOT(slot_process(cv::Mat)));

    while (true) {
      is->run();
      cv::waitKey(20);
    }
  }

  return app.exec();
}
