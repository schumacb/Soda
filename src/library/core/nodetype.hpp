#pragma once

#include <QString>

namespace soda {

class NodeType {
public:
  const std::string ID;
  const QString NAME;
  const QString DESCRIPTION;
};
bool operator==(const NodeType &nl, const NodeType &nr);

} // namespace soda
