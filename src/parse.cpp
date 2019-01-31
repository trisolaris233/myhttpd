#include "parse.h"
#include <cctype>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

namespace tri {

namespace parse {

const std::vector<std::string> MethodSupported = {
    "OPTIONS",
    "GET",
    "POST",
    "HEAD"
};

inline namespace tools {

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

// this function do the parse of a http request report
std::vector<std::string> ParseRequestToLines(const std::string& src) {
    bool cr_flag = false, lf_flag = false;
    std::size_t i = 0;
    std::string tmp;
    std::vector<std::string> desc;

    while(i != src.size()) {
        char current_char = src[i];
        
        if(current_char == '\r') {
            cr_flag = true;
        }
        else if(current_char == '\n') {
            if(cr_flag) { lf_flag = true; }
        }
        else {
            tmp += current_char;
        }
        
        if(cr_flag && lf_flag) {
            if(!tmp.empty()) {
                desc.push_back(tmp);
                cr_flag = lf_flag = false;
                tmp = "";
            }
        }

        i++;
    }
    return desc;
}

std::pair<bool, std::vector<std::pair<std::string, std::string>>> ParseRequest(std::vector<std::string>&& src) {
    std::vector<std::pair<std::string, std::string>> desc;
    int line_number = 1;
    if(src.empty()) {
        return std::make_pair(false, desc);
    }
    // check request-line
    auto str_first_line = src[0];
    std::string word("");
    std::vector<std::string> words;
    for(auto chr : str_first_line) {
        if(chr == ' ') { // space
            if(!word.empty()) {
                words.push_back(word);
                word = "";
            }
        } else {
            word += chr;
        }
    }
    if(!word.empty()) {
        words.push_back(word);
    }
    word = "";

    if(words.size() != 3) {
        return std::make_pair(false, desc);
    }
    if(find(MethodSupported.begin(), MethodSupported.end(), words[0]) == MethodSupported.end()) {
        return std::make_pair(false, desc);
    }
    if(ToUpper(words[2]) != std::string("HTTP/1.1")) {
        return std::make_pair(false, desc);
    }
    desc.push_back(std::make_pair(words[0], words[1]));
    
    bool colon_flag = false;
    std::pair<std::string, std::string> field;
    for(std::size_t i = 1; i < src.size(); ++i) {
        for(auto chr : src[i]) {
            if(chr == ':' && !colon_flag) {
                field.first = word;
                word = "";
                colon_flag = true;
            }
            else {
                word += chr;
            }
        }
        field.second = word;
        word = "";
        ++line_number;
        desc.push_back(field);
        colon_flag = false;
    }
    
    return std::make_pair(true, desc);
}

}
}
