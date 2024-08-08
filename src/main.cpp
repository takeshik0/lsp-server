#include <iostream>
#include "JsonRpc.hpp"
#include "Server.hpp"

int main () {
    std::cout << "hello develop lsp branch!" << std::endl;

    std::string jsonFilePath = "request.json";

    JsonRpc json;
    json.parseRequest(jsonFilePath);

    Server server;
    server.gotoDefinition(json);
    
    return 0;
}