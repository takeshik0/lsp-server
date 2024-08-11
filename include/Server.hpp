#pragma once
#include "JsonRpc.hpp"

class Server {
private:
public:
  range gotoDeclaration(JsonRpc &json);
};