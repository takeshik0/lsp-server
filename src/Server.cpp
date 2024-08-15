#include "Server.hpp"
#include "GotoDeclaration.hpp"
#include "JsonRpc.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

range Server::gotoDeclaration(JsonRpc &json) {
  GotoDeclaration method;
  method.parseParams(json.getParams());

  std::ifstream file(method.getUri());
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string clientFile = buffer.str();

  std::string lineToSearch;
  std::string wordToSearch;

  for (int i = 0, lineCounter = 1; i < clientFile.size(); i++) {
    if (lineCounter == method.getLine()) {
      std::copy(clientFile.begin() + i, clientFile.end(),
                std::back_inserter(lineToSearch));
      wordToSearch = lineToSearch.substr(method.getStartCharacter(),
                                         method.getEndCharacter() -
                                             method.getStartCharacter());
      break;
    }
    if (clientFile[i] == '\n') {
      lineCounter++;
    }
  }
  lineToSearch.clear();

  int lineCounter = 1;
  std::for_each(clientFile.begin(),
                clientFile.begin() + clientFile.find(wordToSearch),
                [&](char ch) {
                  if (ch == '\n') {
                    lineCounter++;
                  }
                });
  std::copy(clientFile.begin() +
                clientFile.rfind("\n", clientFile.find(wordToSearch)) + 1,
            clientFile.begin() +
                clientFile.find("\n", clientFile.find(wordToSearch)),
            std::back_inserter(lineToSearch));

  // auto startOfLine = clientFile.rfind("\n", clientFile.find(wordToSearch));

  range range {.line = lineCounter,
          .start = static_cast<int>(lineToSearch.find(wordToSearch)),
          .end = static_cast<int>(lineToSearch.find(wordToSearch) +
                                  wordToSearch.size() - 1)};

  return range;
}