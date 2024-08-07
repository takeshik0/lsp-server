#include <iostream>
#include "JsonRpcParser.hpp"

int main () {
    std::cout << "hello develop lsp branch!" << std::endl;
    JsonRpcParser parser("{\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42, 23], \"id\": 1}");
    
    return 0;
}