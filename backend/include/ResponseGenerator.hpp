#pragma once
#include "JsonRpc.hpp"
#include <vector>

class ResponceGenerator {
private:
  std::string removeEmptyPosition(const std::string& jsonContent);
public:
  ResponceGenerator(JsonRpc& request, const std::string& responseFilePath, range result);
  ResponceGenerator(JsonRpc& request, const std::string& responseFilePath, std::vector<range> result);
};