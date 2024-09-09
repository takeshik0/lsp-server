#include "GotoDeclaration.hpp"
#include "JsonRpc.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

range GotoDeclaration::gotoDeclaration(JsonRpc &json) {
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

  range range {.line = lineCounter,
          .start = static_cast<int>(lineToSearch.find(wordToSearch)),
          .end = static_cast<int>(lineToSearch.find(wordToSearch) +
                                  wordToSearch.size() - 1)};

  return range;
}

void GotoDeclaration::parseParams(std::string params) {
  std::copy(params.begin() + params.find(URI_KEYWORD) + URI_KEYWORD.size(),
            params.begin() + params.find('}'), std::back_inserter(m_uri));
  std::string tempUri = m_uri.substr(m_uri.find('/'));
  m_uri = tempUri.substr(0, tempUri.find('\"'));

  std::string tempLine = "";
  std::copy_if(params.begin() + params.find(LINE_KEYWORD) + LINE_KEYWORD.size(),
               params.begin() + params.find(START_CHARACTER_KEYWORD),
               std::back_inserter(tempLine),
               [](char ch) { return std::isdigit(ch); });
  m_line = std::stoi(tempLine);

  std::string tempStartCharacter = "";
  std::copy_if(params.begin() + params.find(START_CHARACTER_KEYWORD) +
                   START_CHARACTER_KEYWORD.size(),
               params.begin() + params.find(END_CHARACTER_KEYWORD),
               std::back_inserter(tempStartCharacter),
               [](char ch) { return std::isdigit(ch); });
  m_startCharacter = std::stoi(tempStartCharacter);

  std::string tempEndCharacter = "";
  std::copy_if(params.begin() + params.find(END_CHARACTER_KEYWORD) +
                   END_CHARACTER_KEYWORD.size(),
               params.end(), std::back_inserter(tempEndCharacter),
               [](char ch) { return std::isdigit(ch); });
  m_endCharacter = std::stoi(tempEndCharacter);
}

std::string GotoDeclaration::getUri() { return m_uri; }
int GotoDeclaration::getLine() { return m_line; }
int GotoDeclaration::getStartCharacter() { return m_startCharacter; }
int GotoDeclaration::getEndCharacter() { return m_endCharacter; }