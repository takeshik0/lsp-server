#pragma once
#include <string>
#include <fstream>

class JsonRpc {
private:
    std::string m_jsonrpc;
    std::string m_jsonrpc_version;
    std::string m_method;
    std::string m_params;
    std::string m_id;

    std::string jsonToString(std::string jsonFilePath);
    void parseArgument(const std::string &typeOfArgument, std::string &argument);

public: 
    std::string getJsonrpcVersion();
    std::string getMethod();
    std::string getParams();
    std::string getId();

    void parseRequest(std::string& jsonFilePath);
    JsonRpc() = default;
};