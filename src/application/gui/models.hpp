#pragma once

#include <memory>

#include <QtCore/QObject>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class MyNodeData : public NodeData {
public:
  NodeDataType type() const override {
    return NodeDataType{"MyNodeData", "My Node Data"};
  }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ImageSourceModel : public NodeDataModel {
  Q_OBJECT

public:
  virtual ~ImageSourceModel() {}

public:
  QString caption() const override { return QString("Image Source"); }

  QString name() const override { return QString("ImageSource"); }

  std::unique_ptr<NodeDataModel> clone() const override {
    return std::make_unique<ImageSourceModel>();
  }

public:
  QJsonObject save() const override {
    QJsonObject modelJson;

    modelJson["name"] = name();

    return modelJson;
  }

public:
  unsigned int nPorts(PortType t) const override {
    if (t == PortType::Out) {
      return 1;
    }
    return 0;
  }

  NodeDataType dataType(PortType, PortIndex) const override {
    return MyNodeData().type();
  }

  std::shared_ptr<NodeData> outData(PortIndex) override {
    return std::make_shared<MyNodeData>();
  }

  void setInData(std::shared_ptr<NodeData>, int) override {
    //
  }

  QWidget *embeddedWidget() override { return nullptr; }
};

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ImageSinkModel : public NodeDataModel {
  Q_OBJECT

public:
  virtual ~ImageSinkModel() {}

public:
  QString caption() const override { return QString("Image Sink"); }

  QString name() const override { return QString("ImageSink"); }

  std::unique_ptr<NodeDataModel> clone() const override {
    return std::make_unique<ImageSinkModel>();
  }

public:
  QJsonObject save() const override {
    QJsonObject modelJson;

    modelJson["name"] = name();

    return modelJson;
  }

public:
  unsigned int nPorts(PortType) const override { return 3; }

  NodeDataType dataType(PortType, PortIndex t_portIdx) const override {
    return QtNodes::NodeDataType{"cv::Mat", "Mat" + QString::number(t_portIdx)};
  }

  std::shared_ptr<NodeData> outData(PortIndex) override {
    return std::make_shared<MyNodeData>();
  }

  void setInData(std::shared_ptr<NodeData>, int) override {
    //
  }

  QWidget *embeddedWidget() override { return nullptr; }
};
