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

// this function do the parse of a http request report.
int ParseRequest(const std::string& src, std::vector<std::pair<std::string, std::string>>& desc) {
    bool carriage_return_flag = false,
         line_feed_flag = false;
    std::string tmp;
    std::vector<std::string> words;
    std::size_t i = 0,
                // line number is the line currently treating
                line_number = 1;


    while(i != src.size()) {
        char chr = src[i];
        std::cout << chr;
        // when the character is line-feed
       /* if(chr == '\n') {
            // and the carriage-return flag is set that means a line end
            if(carriage_return_flag) {
                line_feed_flag = true;
            }
        }
        // when space is met
        else if(chr == ' ' || chr == '\r') {
            if(chr == '\r') carriage_return_flag = true;
            if(chr == ' ') {
                words.push_back(tmp);
                tmp = "";
            }
        }
        else {
            tmp += chr;
            std::cout << "tmp = " << tmp << std::endl;
        }*/
        ++i;
    
         // treat one line
        /*if(line_feed_flag) {
            std::cout << "line_feed_flag = true" << std::endl;
            std::cout << "words.size() = " << words.size() << std::endl;
            if(!words.empty()) {
                std::cout << "line_number = " << line_number << std::endl;
                // if in line 1
                // line 1 must fits 'Method SP Request-URI SP HTTP-Version CRLF'
                if(line_number == 1) {
                    if(words.size() != 3) return 0;
                    std::string str_method = words[0],
                                str_uri = words[1],
                                str_http_version = words[2];
                    // judge whether the method is supported
                    if(std::find(MethodSupported.begin(), MethodSupported.end(),str_method) == MethodSupported.end()) {
                        return -1;
                    }
                     
                    desc.push_back(std::make_pair(str_method, str_uri));
                    std::string str_http_version_supported = "HTTP/1.1";
                    desc.push_back(std::make_pair(str_http_version, str_http_version_supported));
                }
                // if not line 1 
                else {
                    if(words.size() < 2) return 0;
                    
                    std::size_t index = 0;
                    for(;index != words.size() && !Trim(words[index]).empty(); ++index);
                    if(index == words.size()) return -2;
                    
                    std::string str_field_name = words[index],
                                str_field_value;
                    for(; index != words.size(); ++index) {
                        str_field_value += words[index];
                    }
                    
                    desc.push_back(std::make_pair(str_field_name, str_field_value));
                }

            }
            words.clear();
            carriage_return_flag = line_feed_flag = false;
            line_number += 1;
        }*/
    }
    return 1;
}
}
}
