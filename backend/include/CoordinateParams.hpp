#pragma once

#include "BaseMethod.hpp"
#include "JsonRpc.hpp"

class CoordinateParams : public BaseMethod {
private:
  std::string m_uri;
  int m_line;
  int m_startCharacter;
  int m_endCharacter;
public:
  CoordinateParams(std::string params);
  void parseParams(std::string params) override;
  std::string getUri();
  int getLine();
  int getStartCharacter();
  int getEndCharacter();
};