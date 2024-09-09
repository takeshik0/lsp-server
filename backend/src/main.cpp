#include "Server.hpp"
#include <iostream>

int main() {

  const std::string requestFilePath = "/home/takeshi/c++_projects/lsp-server/request.json";
  const std::string responseFilePath = "/home/takeshi/c++_projects/lsp-server/response.json";

  Server server(requestFilePath, responseFilePath);

  std::cout << "hello develop lsp branch!" << std::endl;

  return 0;
}