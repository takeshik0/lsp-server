#pragma once

#include "JsonRpc.hpp"
#include "GotoDefinition.hpp"

class Server {
private:
public:
  void gotoDefinition(JsonRpc &json);
};