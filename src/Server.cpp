#include "Server.hpp"
#include "GotoDeclaration.hpp"
#include <fstream>
#include <string>

range Server::gotoDeclaration(JsonRpc &json) {
  GotoDeclaration method;
  method.parseParams(json.getParams());

  std::ifstream file(method.getUri());
  std::string clientFile = "";
  std::string line;
  for (int i = 1; std::getline(file, line) && i <= method.getLine(); i++) {
    clientFile += line;
  }

  std::string wordToSearch =
      line.substr(method.getStartCharacter(),
                  method.getEndCharacter() - method.getStartCharacter());

  return {.start = clientFile.find(wordToSearch),
          .end = clientFile.find(wordToSearch) + wordToSearch.size()};
}