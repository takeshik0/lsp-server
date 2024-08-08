#include "Server.hpp"
#include "GotoDefinition.hpp"
#include <fstream>

void Server::gotoDefinition(JsonRpc &json) {
  GotoDefinition method;
  method.parseParams(json.getParams());
  
  std::ifstream file(method.getUri());


}