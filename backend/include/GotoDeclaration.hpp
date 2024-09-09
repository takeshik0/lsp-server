#pragma once
#include "BaseMethod.hpp"
#include "JsonRpc.hpp"

class GotoDeclaration : public BaseMethod {
private:
  std::string m_uri;
  int m_line;
  int m_startCharacter;
  int m_endCharacter;
public:
  range gotoDeclaration(JsonRpc &json);
  
  void parseParams(std::string params) override;
  std::string getUri();
  int getLine();
  int getStartCharacter();
  int getEndCharacter();
};