#pragma once

#include <QDataStream>
#include <QtCore/qglobal.h>

struct Blob {
  quint32 area;
  quint16 left;
  quint16 right;
  quint16 top;
  quint16 bottom;
  int x_cg() { return (right - left) / 2; }
  int y_cg() { return (bottom - top) / 2; }
};

inline bool operator==(const Blob &leftBlob, const Blob &rightBlob) {
  return leftBlob.area == rightBlob.area && leftBlob.left == rightBlob.left &&
         leftBlob.right == rightBlob.right && leftBlob.top == rightBlob.top &&
         leftBlob.bottom == rightBlob.bottom;
}

inline bool operator<(const Blob &leftBlob, const Blob &rightBlob) {
  return leftBlob.area < rightBlob.area;
}

inline bool operator<=(const Blob &leftBlob, const Blob &rightBlob) {
  return leftBlob.area <= rightBlob.area;
}

inline bool operator>(const Blob &leftBlob, const Blob &rightBlob) {
  return leftBlob.area > rightBlob.area;
}

inline bool operator>=(const Blob &leftBlob, const Blob &rightBlob) {
  return leftBlob.area >= rightBlob.area;
}

inline QDataStream &operator<<(QDataStream &stream, const Blob &blob) {

  stream << blob.area;
  stream << blob.left;
  stream << blob.right;
  stream << blob.top;
  stream << blob.bottom;
  return stream;
}

inline QDataStream &operator>>(QDataStream &stream, Blob &blob) {

  stream >> blob.area;
  stream >> blob.left;
  stream >> blob.right;
  stream >> blob.top;
  stream >> blob.bottom;
  return stream;
}
