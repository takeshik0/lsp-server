#include "JsonRpc.hpp"
#include "ResponseGenerator.hpp"
#include "Server.hpp"
#include <iostream>

int main() {

  std::string jsonFilePath = "request.json";

  JsonRpc json;
  json.parseRequest(jsonFilePath);

  Server server;
  auto result = server.gotoDeclaration(json);

  ResponceGenerator response(json, result);
  std::cout << "hello develop lsp branch!" << std::endl;

  return 0;
}