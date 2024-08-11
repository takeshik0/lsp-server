#pragma once
#include "BaseMethod.hpp"

class GotoDeclaration : public BaseMethod {
private:
  std::string m_uri;
  int m_line;
  int m_startCharacter;
  int m_endCharacter;

  void parsePosition(std::string params);

public:
  void parseParams(std::string params) override;
  std::string getUri();
  int getLine();
  int getStartCharacter();
  int getEndCharacter();
};