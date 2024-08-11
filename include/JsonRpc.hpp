#pragma once
#include <cstddef>
#include <string>

const std::string JSONRPC_VAR_KEYWORD = "jsonrpc";
const std::string METHOD_KEYWORD = "method";
const std::string PARAMS_KEYWORD = "params";
const std::string ID_KEYWORD = "id";

const std::string URI_KEYWORD = "uri";
const std::string LINE_KEYWORD = "line";
const std::string START_CHARACTER_KEYWORD = "startCharacter";
const std::string END_CHARACTER_KEYWORD = "endCharacter";

struct range {
  std::size_t start;
  std::size_t end;
};

class JsonRpc {
private:
  std::string m_jsonrpc;
  std::string m_jsonrpc_version;
  std::string m_method;
  std::string m_params;
  std::string m_id;

  std::string jsonToString(const std::string& jsonFilePath);
  void parseArgument(const std::string &typeOfArgument, std::string &argument);

public:
  std::string getJsonrpc();
  std::string getJsonrpcVersion();
  std::string getMethod();
  std::string getParams();
  std::string getId();

  void parseRequest(std::string &jsonFilePath);
  JsonRpc() = default;
};