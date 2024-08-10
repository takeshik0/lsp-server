#pragma once
#include <string>

class BaseMethod {
public:
  virtual void parseParams(std::string params) = 0;
  virtual ~BaseMethod() = default;
};
