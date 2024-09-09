#pragma once
#include "JsonRpc.hpp"
#include <vector>

class ResponceGenerator {
private:
  std::string removeEmptyPosition(const std::string& jsonContent);
public:
  ResponceGenerator(JsonRpc& jsonrpc, range result);
  ResponceGenerator(JsonRpc& jsonrpc, std::vector<range> result);
};