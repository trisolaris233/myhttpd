#include <string>

namespace tri {
    std::string ToLower(const std::string& str);
    std::string ToUpper(const std::string& str);
    std::string Trim(const std::string& str, const char* charlist = "\0\t\n\r ");
}