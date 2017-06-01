#pragma once

#include <QtCore/qglobal.h>

#include <nodes/NodeData>
#include <nodes/NodeModel>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace soda {
  namespace plugin {
    namespace corenodes {


class ImagePreviewModel : public QtNodes::SimpleNodeModel {
private:
  QLabel *m_label;

public:
  ImagePreviewModel();
  virtual ~ImagePreviewModel();

  // No copy or assignment

  ImagePreviewModel(const ImagePreviewModel &other) = delete;
  ImagePreviewModel operator=(const ImagePreviewModel &other) = delete;

  // NodeDataModel interface
public:
  QString name() const;
  std::unique_ptr<QtNodes::NodeDataModel> clone() const;
  unsigned int nPorts(QtNodes::PortType portType) const;
  QtNodes::NodeDataType dataType(QtNodes::PortType portType,
                                 QtNodes::PortIndex portIndex) const;
  QWidget *embeddedWidget();

  // Serializable interface
public:
  QJsonObject save() const;
  void restore(const QJsonObject &);
};

    } // namespace corenodes
    } // namespace plugin
    } // namespace soda
