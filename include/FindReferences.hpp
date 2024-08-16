#pragma once
#include "GotoDeclaration.hpp"
#include <vector>

class FindReferences : public GotoDeclaration{
private:
  std::string m_uri;
  int m_line;
  int m_startCharacter;
  int m_endCharacter;

public:
  std::vector<range> findReferences(JsonRpc &json);
  
  std::string getUri();
  int getLine();
  int getStartCharacter();
  int getEndCharacter();
};