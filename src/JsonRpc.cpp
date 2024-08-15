#include "JsonRpc.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>

std::string JsonRpc::jsonToString(const std::string &jsonFilePath) {
  std::ifstream jsonFile(jsonFilePath);
  if (!jsonFile.is_open()) {
    throw std::runtime_error("Could not open file");
  }
  std::stringstream buffer;
  buffer << jsonFile.rdbuf();
  return buffer.str();
}

void JsonRpc::parseArgument(const std::string &typeOfArgument,
                            std::string &argument) {
  if (typeOfArgument == PARAMS_KEYWORD) {
    auto startPos = m_jsonrpc.begin() + m_jsonrpc.find(typeOfArgument) +
                    typeOfArgument.size() + 3;
    std::copy(startPos,
              m_jsonrpc.begin() +
                  m_jsonrpc.find(ID_KEYWORD, startPos - m_jsonrpc.begin()),
              std::back_inserter(argument));
    argument.erase(argument.begin() + argument.rfind(','), argument.end());
    return;
  }
  m_jsonrpc.find(typeOfArgument);
  int CHARACTERS_TO_SKIP = 4;
  if (typeOfArgument == "id") {
    CHARACTERS_TO_SKIP--;
    auto startPos = m_jsonrpc.begin() + m_jsonrpc.find(typeOfArgument) +
                    typeOfArgument.size() + CHARACTERS_TO_SKIP;

    std::copy_if(startPos, m_jsonrpc.end(), std::back_inserter(argument),
                 [](char ch) { return std::isdigit(ch); });
  }
  auto startPos = m_jsonrpc.begin() + m_jsonrpc.find(typeOfArgument) +
                  typeOfArgument.size() + CHARACTERS_TO_SKIP;

  std::copy(startPos,
            m_jsonrpc.begin() +
                m_jsonrpc.find('\"', startPos - m_jsonrpc.begin()),
            std::back_inserter(argument));
  return;
}

std::string JsonRpc::getJsonrpcVersion() { return m_jsonrpc_version; }
std::string JsonRpc::getMethod() { return m_method; }
std::string JsonRpc::getParams() { return m_params; }
std::string JsonRpc::getId() { return m_id; }
std::string JsonRpc::getJsonrpc() { return m_jsonrpc; }

void JsonRpc::parseRequest(std::string &jsonFilePath) {
  m_jsonrpc = jsonToString(jsonFilePath);

  parseArgument(JSONRPC_VAR_KEYWORD, m_jsonrpc_version);
  parseArgument(METHOD_KEYWORD, m_method);
  parseArgument(PARAMS_KEYWORD, m_params);
  parseArgument(ID_KEYWORD, m_id);
}
