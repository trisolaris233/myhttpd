#include "tools.h"
#include <cstring>

namespace tri {
    std::string ToLower(const std::string& str) {
        std::string str_target;
        for(auto chr : str) {
            str_target += std::tolower(chr);
        }
        return str_target;
    }

    std::string ToUpper(const std::string& str) {
        std::string str_target;
        for(auto chr : str) {
            str_target += std::toupper(chr);
        }
        return str_target;
    }

    std::string Trim(const std::string& str, const char* charlist) {
        std::string str_target;
        for(auto chr : str) {
            if(strchr(charlist, chr) == NULL)
                continue;
            str_target += chr;
        }
        return str_target;
    }
}