#include "ResponseGenerator.hpp"
#include "JsonRpc.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>

ResponceGenerator::ResponceGenerator(JsonRpc &json, range result) {
  std::ofstream response("response.json");
  std::string tempFileContent = json.getJsonrpc();

  auto newEnd = std::remove_if(
      tempFileContent.begin() + tempFileContent.find(START_CHARACTER_KEYWORD),
      tempFileContent.begin() + tempFileContent.find(ID_KEYWORD), [](char ch) { return std::isdigit(ch); });

  tempFileContent.erase(newEnd, tempFileContent.begin() + tempFileContent.find(ID_KEYWORD));

  tempFileContent.replace(tempFileContent.find(PARAMS_KEYWORD),
                          PARAMS_KEYWORD.size(), "result");
  tempFileContent.insert(tempFileContent.find(START_CHARACTER_KEYWORD) +
                             START_CHARACTER_KEYWORD.size() +
                             3 /* ":  3 symbols (need to fix)*/,
                         std::to_string(result.start));
  tempFileContent.insert(tempFileContent.find(END_CHARACTER_KEYWORD) +
                             END_CHARACTER_KEYWORD.size() +
                             3 /* ":  3 symbols (need to fix)*/,
                         std::to_string(result.end));
  response << tempFileContent;
}