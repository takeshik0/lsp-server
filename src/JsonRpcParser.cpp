#include "JsonRpcParser.hpp"
#include <cctype>

void JsonRpcParser::parseArgument(const std::string &typeOfArgument,
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
        while (m_jsonrpc[pos] != ']' &&  m_jsonrpc[pos] != '}' && pos < m_jsonrpc.size()) {
          if (m_jsonrpc[pos] != ':' && !std::isspace(m_jsonrpc[pos])) {
            argument += m_jsonrpc[pos];
          }
          pos++;
        }
        argument += m_jsonrpc[pos];
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

JsonRpcParser::JsonRpcParser(std::string jsonrpc) {
  m_jsonrpc = jsonrpc;

  const std::string JSONRPC_VAR = "jsonrpc";
  const std::string METHOD = "method";
  const std::string PARAMS = "params";
  const std::string ID = "id";

  parseArgument(JSONRPC_VAR, m_jsonrpc_version);
  parseArgument(METHOD, m_method);
  parseArgument(PARAMS, m_params);
  parseArgument(ID, m_id);
}