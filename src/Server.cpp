#include "Server.hpp"
#include "GotoDefinition.hpp"
#include <fstream>
#include <string>

void Server::gotoDefinition(JsonRpc &json) {
  GotoDefinition method;
  method.parseParams(json.getParams());
  
  std::ifstream file(method.getUri());
  std::string line;
  for(int i = 0; i < method.getLine(); i++) {
    std::getline(file, line);
  }
  
  std::string wordToSearch = line.substr(method.getStartCharacter(), method.getEndCharacter() - method.getStartCharacter());

  int definition = 

}