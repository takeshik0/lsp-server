#include "Server.hpp"
#include "GotoDeclaration.hpp"
#include "JsonRpc.hpp"
#include "ResponseGenerator.hpp"
#include "FindReferences.hpp"

Server::Server(const std::string &jsonFilePath) {

  JsonRpc json;
  json.parseRequest(jsonFilePath);

  if (json.getMethod() == "gotoDeclaration") {
    GotoDeclaration result;
    ResponceGenerator response(json, result.gotoDeclaration(json));
  } else if (json.getMethod() == "findReferences") {
    FindReferences result;
    ResponceGenerator response(json, result.findReferences(json));
   } else if (json.getMethod() == "renameSymbol") {
    FindReferences result;
    ResponceGenerator response(json, result.findReferences(json));
  };
}