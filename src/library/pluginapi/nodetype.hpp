#pragma once

#include <QString>
#include <QtCore/qglobal.h>

namespace soda {

class NodeType {
private:
  std::string m_id;
  QString m_name;
  QString m_description;

public:
  inline NodeType(std::string id, QString name, QString description)
      : m_id{id}, m_name{name}, m_description{description} {}

  inline const std::string &getID() const { return m_id; }
  inline const QString &getName() const { return m_name; }
  inline const QString &getDescription() const { return m_description; }

  inline bool operator==(const NodeType &other) { return m_id == other.m_id; }
};

} // namespace soda
