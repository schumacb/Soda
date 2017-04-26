#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <QObject>
#include <QRunnable>

namespace soda {

namespace pluginapi {

class Algorithm : public QObject {

protected:
  Algorithm(QObject *parrent = 0) : QObject(parrent) {}

public:
  virtual ~Algorithm() {}
  virtual void setConfiguration(QJsonDocument configuration) = 0;

public slots:
  virtual void run() = 0;
};

} // namespace pluginapi

} // namespace soda

#endif // ALGORITHM_HPP
