#pragma once

#include <iostream>

struct Version {
  unsigned short major;
  unsigned short minor;
  unsigned short patch;
};

inline std::ostream &operator<<(std::ostream &os, const Version &v) {
  os << v.major << "." << v.minor << "." << v.patch;
  return os;
}

inline bool operator==(const Version &v1, const Version &v2) {
  return (v1.major == v2.major && v1.minor == v2.minor && v1.patch == v2.patch);
}

inline bool operator!=(const Version &v1, const Version &v2) {
  return (v1.major != v2.major || v1.minor != v2.minor || v1.patch != v2.patch);
}

inline bool operator<(const Version &v1, const Version &v2) {
  return (v1.major < v2.major) ||
         (v1.major == v2.major && v1.minor < v2.minor) ||
         (v1.major == v2.major && v1.minor == v2.minor && v1.patch < v2.patch);
}

inline bool operator<=(const Version &v1, const Version &v2) {
  return (v1.major < v2.major) ||
         (v1.major == v2.major && v1.minor < v2.minor) ||
         (v1.major == v2.major && v1.minor == v2.minor && v1.patch <= v2.patch);
}

inline bool operator>(const Version &v1, const Version &v2) {
  return (v1.major > v2.major) ||
         (v1.major == v2.major && v1.minor > v2.minor) ||
         (v1.major == v2.major && v1.minor == v2.minor && v1.patch > v2.patch);
}

inline bool operator>=(const Version &v1, const Version &v2) {
  return (v1.major > v2.major) ||
         (v1.major == v2.major && v1.minor > v2.minor) ||
         (v1.major == v2.major && v1.minor == v2.minor && v1.patch >= v2.patch);
}
