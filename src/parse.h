#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>
#include "request.h"
namespace tri {

namespace parse {

std::vector<std::string> ParseRequestToLines(const std::string& src);
std::pair<bool, std::vector<std::pair<std::string, std::string>>> ParseRequest(std::vector<std::string>&& src);
}


}
#endif
