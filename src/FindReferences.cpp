#include "FindReferences.hpp"
#include "JsonRpc.hpp"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>

void FindReferences::parseParams(std::string params) {
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

std::string FindReferences::getUri() { return m_uri; }
int FindReferences::getLine() { return m_line; }
int FindReferences::getStartCharacter() { return m_startCharacter; }
int FindReferences::getEndCharacter() { return m_endCharacter; }

std::vector<range> FindReferences::findReferences(JsonRpc &json) {
  std::vector<range> result;
  FindReferences method;
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

  std::string tempClientFile = clientFile;
  tempClientFile.push_back('\n');
  std::string tempLine;
  size_t startOftempLine = 0;
  int lineCounter = 1;
  while (tempClientFile.find('\n') != std::string::npos) {
    tempLine =
        tempClientFile.substr(startOftempLine, tempClientFile.find('\n'));
    if (tempLine.find(wordToSearch) != std::string::npos) {
      range tempRange;
      tempRange.line = lineCounter;
      tempRange.start = tempLine.find(wordToSearch);
      tempRange.end = tempRange.start + wordToSearch.size();
      result.push_back(tempRange);
    }
    lineCounter++;
    tempClientFile = tempClientFile.substr(tempClientFile.find('\n') + 1);
  }

  return result;
}
