#include "Server.hpp"
#include "GotoDefinition.hpp"
#include <fstream>
#include <string>

range Server::gotoDefinition(JsonRpc &json) {
  GotoDefinition method;
  method.parseParams(json.getParams());

  std::ifstream file(method.getUri());
  std::string exampleFile = "";
  std::string line;
  for (int i = 1; std::getline(file, line) && i <= method.getLine(); i++) {
    exampleFile += line;
  }

  std::string wordToSearch =
      line.substr(method.getStartCharacter(),
                  method.getEndCharacter() - method.getStartCharacter());

  return {.start = exampleFile.find(wordToSearch),
          .end = exampleFile.find(wordToSearch) + wordToSearch.size()};
}