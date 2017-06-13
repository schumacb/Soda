#pragma once

#include <iostream>

namespace soda {

class Version {
public:
  unsigned short MAJOR;
  unsigned short MINOR;
  unsigned short PATCH;
};

inline std::ostream &operator<<(std::ostream &os, const Version &v) {
  os << v.MAJOR << "." << v.MINOR << "." << v.PATCH;
  return os;
}

inline bool operator==(const Version &v1, const Version &v2) {
  return (v1.MAJOR == v2.MAJOR && v1.MINOR == v2.MINOR && v1.PATCH == v2.PATCH);
}

inline bool operator!=(const Version &v1, const Version &v2) {
  return (v1.MAJOR != v2.MAJOR || v1.MINOR != v2.MINOR || v1.PATCH != v2.PATCH);
}

inline bool operator<(const Version &v1, const Version &v2) {
  return (v1.MAJOR < v2.MAJOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR < v2.MINOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR == v2.MINOR && v1.PATCH < v2.PATCH);
}

inline bool operator<=(const Version &v1, const Version &v2) {
  return (v1.MAJOR < v2.MAJOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR < v2.MINOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR == v2.MINOR && v1.PATCH <= v2.PATCH);
}

inline bool operator>(const Version &v1, const Version &v2) {
  return (v1.MAJOR > v2.MAJOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR > v2.MINOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR == v2.MINOR && v1.PATCH > v2.PATCH);
}

inline bool operator>=(const Version &v1, const Version &v2) {
  return (v1.MAJOR > v2.MAJOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR > v2.MINOR) ||
         (v1.MAJOR == v2.MAJOR && v1.MINOR == v2.MINOR && v1.PATCH >= v2.PATCH);
}

} // namespace soda
