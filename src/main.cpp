#include "JsonRpc.hpp"
#include "ResponseGenerator.hpp"
#include "Server.hpp"
#include <iostream>

int main() {
  std::cout << "hello develop lsp branch!" << std::endl;

  std::string jsonFilePath = "request.json";

  JsonRpc json;
  json.parseRequest(jsonFilePath);

  Server server;
  server.gotoDefinition(json);

  ResponceGenerator response(json, server.gotoDefinition(json));

  return 0;
}