#include "exception.hpp"

using namespace soda;

void NotYetImplemented::raise() const { throw * this; }

QException *NotYetImplemented::clone() const { return new NotYetImplemented(); }

void UnsupportedType::raise() const { throw * this; }

QException *UnsupportedType::clone() const { return new UnsupportedType(); }

void InvalidConfiguration::raise() const { throw * this; }

QException *InvalidConfiguration::clone() const {
  return new InvalidConfiguration();
}
