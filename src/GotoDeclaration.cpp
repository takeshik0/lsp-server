#include "GotoDeclaration.hpp"
#include "JsonRpc.hpp"
#include <cctype>

void GotoDeclaration::parsePosition(std::string params) {}

void GotoDeclaration::parseParams(std::string params) {
  for (int pos = 0; pos < params.size(); pos++) {
    if (params[pos] == '"') {
      std::string keyword = "";
      pos++;
      while (params[pos] != '"') {
        keyword += params[pos];
        pos++;
      }
      pos++;
      if (keyword == URI_KEYWORD) {
        while (params[pos] != '}' && pos < params.size()) {
          if (params[pos] != ' ' && params[pos] != '"' && params[pos] != ':') {
            m_uri += params[pos];
          }
          pos++;
        }
      } else if (keyword == LINE_KEYWORD) {
        std::string line = "";
        while (params[pos] != ',' && pos < params.size()) {
          if (std::isdigit(params[pos])) {
            line += params[pos];
          }
          pos++;
        }
        m_line = std::stoi(line);
      } else if (keyword == START_CHARACTER_KEYWORD) {
        std::string startCharacter = "";
        while (params[pos] != ',' && pos < params.size()) {
          if (std::isdigit(params[pos])) {
            startCharacter += params[pos];
          }
          pos++;
        }
        m_startCharacter = std::stoi(startCharacter);
      } else if (keyword == END_CHARACTER_KEYWORD) {
        std::string endCharacter = "";
        while (params[pos] != '}' && pos < params.size()) {
          if (std::isdigit(params[pos])) {
            endCharacter += params[pos];
          }
          pos++;
        }
        m_endCharacter = std::stoi(endCharacter);
      }
    }
  }
}

std::string GotoDeclaration::getUri() { return m_uri; }
int GotoDeclaration::getLine() { return m_line; }
int GotoDeclaration::getStartCharacter() { return m_startCharacter; }
int GotoDeclaration::getEndCharacter() { return m_endCharacter; }