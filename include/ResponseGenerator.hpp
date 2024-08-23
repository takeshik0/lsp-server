#pragma once
#include "JsonRpc.hpp"
#include <vector>

class ResponceGenerator {
private:
public:
  ResponceGenerator(JsonRpc& jsonrpc, range result);
  ResponceGenerator(JsonRpc& jsonrpc, std::vector<range> result);
};