#include "JsonRpc.hpp"
#include "ResponseGenerator.hpp"
#include <fstream>

ResponceGenerator::ResponceGenerator(JsonRpc& json, range result) {
  std::ofstream response("response.json");
  std::string tempFileContent = json.getJsonrpc();
  tempFileContent.replace(tempFileContent.find(PARAMS_KEYWORD), PARAMS_KEYWORD.size(), "result");
  tempFileContent.replace(tempFileContent.find(START_CHARACTER_KEYWORD) + 3/* ":  3 symbols (need to fix)*/, std::to_string(result.start).size(), std::to_string(result.start));
  tempFileContent.replace(tempFileContent.find(END_CHARACTER_KEYWORD) + 3/* ":  3 symbols (need to fix)*/, std::to_string(result.end).size(), std::to_string(result.end));
  response  << tempFileContent;
}