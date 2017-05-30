#include "exception.hpp"

void soda::NotYetImplemented::raise() const { throw * this; }

QException *soda::NotYetImplemented::clone() const {
  return new NotYetImplemented();
}

void soda::UnsupportedType::raise() const { throw * this; }

QException *soda::UnsupportedType::clone() const {
  return new UnsupportedType();
}
