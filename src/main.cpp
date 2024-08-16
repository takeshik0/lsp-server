#include "Server.hpp"
#include <iostream>

int main() {

  const std::string jsonFilePath = "request.json";

  Server server(jsonFilePath);

  std::cout << "hello develop lsp branch!" << std::endl;

  return 0;
}