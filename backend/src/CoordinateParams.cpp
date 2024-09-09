#include "CoordinateParams.hpp"
#include <algorithm>

CoordinateParams::CoordinateParams(std::string params) { parseParams(params); }

void CoordinateParams::parseParams(std::string params) {
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

std::string CoordinateParams::getUri() { return m_uri; }
int CoordinateParams::getLine() { return m_line; }
int CoordinateParams::getStartCharacter() { return m_startCharacter; }
int CoordinateParams::getEndCharacter() { return m_endCharacter; }
