#pragma once
#include "JsonRpc.hpp"

class Server {
private:
public:
  range gotoDefinition(JsonRpc &json);
};