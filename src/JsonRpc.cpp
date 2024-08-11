#include "JsonRpc.hpp"
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
  for (int pos = 0; pos < m_jsonrpc.size(); pos++) {
    if (m_jsonrpc[pos] == '"') {
      std::string keyword = "";
      pos++;
      for (int i = pos; m_jsonrpc[i] != '"' && i - pos < typeOfArgument.size();
           i++) {
        keyword += m_jsonrpc[i];
        pos++;
      }
      if (keyword == typeOfArgument && typeOfArgument == "params") {
        pos++;

        while (m_jsonrpc[pos] != '{' && pos < m_jsonrpc.size()) {
          pos++;
        }

        int braceCount = 0;
        int end = pos;

        do {
          if (m_jsonrpc[end] == '{') {
            braceCount++;
          } else if (m_jsonrpc[end] == '}') {
            braceCount--;
          }
          end++;
        } while (braceCount > 0 && end < m_jsonrpc.size());

        argument = m_jsonrpc.substr(pos, end - pos);

      } else if (keyword == typeOfArgument) {
        pos++;
        while (m_jsonrpc[pos] != ',' && pos < m_jsonrpc.size()) {
          if (m_jsonrpc[pos] != ' ' && m_jsonrpc[pos] != '"' &&
              m_jsonrpc[pos] != ':' && m_jsonrpc[pos] != '}') {
            argument += m_jsonrpc[pos];
          }
          pos++;
        }
      }
    }
  }
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
