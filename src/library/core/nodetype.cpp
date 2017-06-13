#include "nodetype.hpp"

using namespace soda;

bool operator==(const NodeType &nl, const NodeType &nr) {
  return nl.ID == nr.ID;
}
