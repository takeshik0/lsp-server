#include "FindReferences.hpp"
#include "JsonRpc.hpp"

std::vector<range> FindReferences::findReferences(JsonRpc &json) {
  std::vector<range> result;
  parseParams(json.getParams());
  auto smth = m_startCharacter;
  return result;
}