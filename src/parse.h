#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>

namespace tri {

namespace parse {


inline namespace tools {

    std::string ToUpper(const std::string& str);
    std::string Trim(const std::string& str, const char* charlist = "\0\t\n\r ");
}



int ParseRequest(const std::string& src, std::vector<std::pair<std::string, std::string>>& desc);
}


}
#endif
