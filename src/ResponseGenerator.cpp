#include "ResponseGenerator.hpp"
#include "JsonRpc.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

std::string
ResponceGenerator::removeEmptyPosition(const std::string &jsonContent) {
  std::string tempFileContent = jsonContent;

  std::size_t positionStart = tempFileContent.find("\"position\": {");
  if (positionStart != std::string::npos) {
    std::size_t positionEnd = tempFileContent.find("}", positionStart);

    if (positionEnd != std::string::npos) {
      tempFileContent.erase(positionStart, positionEnd - positionStart + 1);

      std::size_t commaPos = tempFileContent.find(",", positionStart);
      if (commaPos != std::string::npos && (commaPos - positionStart) < 3) {
        tempFileContent.erase(commaPos, 1);
      }
    }
  }

  // shitcode
  std::size_t emptyLinePosition = tempFileContent.find("\"position");
  tempFileContent.erase(emptyLinePosition - 3, 3);

  return tempFileContent;
}

ResponceGenerator::ResponceGenerator(JsonRpc &json, range result) {
  std::ofstream response("response.json");
  std::string tempFileContent = json.getJsonrpc();

  auto newEnd = std::remove_if(
      tempFileContent.begin() + tempFileContent.find(LINE_KEYWORD),
      tempFileContent.begin() + tempFileContent.find(ID_KEYWORD),
      [](char ch) { return std::isdigit(ch); });

  tempFileContent.erase(newEnd, tempFileContent.begin() +
                                    tempFileContent.find(ID_KEYWORD));

  tempFileContent.replace(tempFileContent.find(PARAMS_KEYWORD),
                          PARAMS_KEYWORD.size(), "result");

  tempFileContent.insert(tempFileContent.find(LINE_KEYWORD) +
                             LINE_KEYWORD.size() +
                             3 /* ":  3 symbols (need to fix)*/,
                         std::to_string(result.line));
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

ResponceGenerator::ResponceGenerator(JsonRpc &json, std::vector<range> result) {
  std::ofstream response("response.json");
  std::string tempFileContent = json.getJsonrpc();

  auto newEnd = std::remove_if(
      tempFileContent.begin() + tempFileContent.find(LINE_KEYWORD),
      tempFileContent.begin() + tempFileContent.find(ID_KEYWORD),
      [](char ch) { return std::isdigit(ch); });

  std::string positionSegment;
  std::copy(tempFileContent.begin() + tempFileContent.find(POSITION_KEYWORD) -
                1,
            tempFileContent.begin() + tempFileContent.find(ID_KEYWORD),
            std::back_inserter(positionSegment));

  positionSegment.erase(positionSegment.begin() + positionSegment.find('}') + 1,
                        positionSegment.end());

  positionSegment.insert(0, ",\n\t\t");

  tempFileContent.erase(newEnd, tempFileContent.begin() +
                                    tempFileContent.find(ID_KEYWORD));

  tempFileContent.replace(tempFileContent.find(PARAMS_KEYWORD),
                          PARAMS_KEYWORD.size(), "result");
  int num = 0;
  for (const auto &it : result) {
    num++;

    positionSegment.insert(
        positionSegment.find(POSITION_KEYWORD) +
            POSITION_KEYWORD.size() /* ":  3 symbols (need to fix)*/,
        std::to_string(num));
    positionSegment.insert(positionSegment.find(LINE_KEYWORD) +
                               LINE_KEYWORD.size() +
                               3 /* ":  3 symbols (need to fix)*/,
                           std::to_string(it.line));
    positionSegment.insert(positionSegment.find(START_CHARACTER_KEYWORD) +
                               START_CHARACTER_KEYWORD.size() +
                               3 /* ":  3 symbols (need to fix)*/,
                           std::to_string(it.start));
    positionSegment.insert(positionSegment.find(END_CHARACTER_KEYWORD) +
                               END_CHARACTER_KEYWORD.size() +
                               3 /* ":  3 symbols (need to fix)*/,
                           std::to_string(it.end));
    tempFileContent.insert(
        tempFileContent.find('}', tempFileContent.find(POSITION_KEYWORD)) + 1,
        positionSegment);
    positionSegment.erase(
        std::remove_if(positionSegment.begin(), positionSegment.end(),
                       [](char ch) { return std::isdigit(ch); }),
        positionSegment.end());
  }
  response << removeEmptyPosition(tempFileContent);
  ;
}