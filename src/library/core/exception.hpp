#pragma once

#include <QException>

namespace soda {

class NotYetImplemented : public QException {

  // QException interface
public:
  void raise() const override;
  QException *clone() const override;
};

class UnsupportedType : public QException {

  // QException interface
public:
  void raise() const;
  QException *clone() const;
};

} // namespace soda
