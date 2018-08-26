#pragma once

#include <QObject>

namespace soda {

class BlobDetect : public QObject {
  Q_OBJECT
protected:

public:
  explicit BlobDetect(QObject *parent = 0);
};

} // namespace Soda
