#pragma once
#include "CoordinateParams.hpp"

#include <vector>

class FindReferences : public BaseMethod{
private:
  std::string m_uri;
  int m_line;
  int m_startCharacter;
  int m_endCharacter;

public:
  void parseParams(std::string params) override;

  std::vector<range> findReferences(JsonRpc &json);
  
  std::string getUri();
  int getLine();
  int getStartCharacter();
  int getEndCharacter();
};