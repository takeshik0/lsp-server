#pragma once
#include <string>

class JsonRpcParser {
private:
    std::string m_jsonrpc;
    std::string m_jsonrpc_version;
    std::string m_method;
    std::string m_params;
    std::string m_id;
public: 
    void parseArgument(const std::string &typeOfArgument, std::string &argument);
    JsonRpcParser(std::string jsonrpc);
};