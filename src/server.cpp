#include "tools.h"
#include "server.h"
#include "request.h"
#include "response.h"
#include "compress.h"
#include <memory>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

namespace tri {
namespace http {

    HttpdBase::~HttpdBase() {}
    
    void HttpdImpl::SetHttpRootDir(const std::string& dir) {
        if(dir.empty()) return;
        // check if postfix / but isn't the root of system.
        if(dir[dir.size() - 1] == '/' && dir.size() > 1) {
             root_dir_.assign(dir.begin(), dir.end() - 1);
        } else {
            root_dir_.assign(dir);
        }
    }

    void HttpdImpl::SetListener(HttpdImpl::listener_type listener) {
        listener_ = listener;
    }

    std::string HttpdImpl::GetHttpRootDir() const {
        return root_dir_;
    }

    HttpdImpl::HttpdImpl(unsigned int port, const char* ip) : 
        root_dir_(".") {
        socket_.Create(port, ip);
    }


    void HttpdImpl::Start() {
        socket_.Listen([=](tri::TcpSocket* psocket, std::shared_ptr<char> receiver) {
            listener_(this, Request(receiver.get()));
        });
    }

    void HttpdImpl::Respond(const Response& response) {
        socket_.Send(response.Str());
    }

    bool IsImage(const std::string& extension) {
        std::vector<std::string> extension_supported = {
            "JPG", "GIF", "PNG", "ICO", "WEBP"
        };
        return find(extension_supported.begin(), extension_supported.end(), ToUpper(extension)) != extension_supported.end();
    }

    std::string GetExtension(const std::string& uri) {
        std::string extension;
        for(auto itr = uri.rbegin(); itr != uri.rend(); ++itr) {
            if(*itr == '.') {
                return std::string(extension.rbegin(), extension.rend());
            } else {
                extension += *itr;
            }
        }
        return std::string(extension.rbegin(), extension.rend());
    }

    std::string AdjustURI(const std::string& uri) {
        auto tokens = Split(uri, '/');
        std::string res = "/";
        
        for(auto token : tokens) {
            if(!token.empty()) {
                res.append(token);
            }
        }
        return res;
    }

    std::string ReadFile(const std::string& path) {
        struct stat struct_stat;
        if(::stat(path.c_str(), &struct_stat) == -1) {
            std::cerr << ::strerror(errno) << std::endl;
            return std::string();
        }

        // read the whole file in one time
        std::string str;
        if(S_ISREG(struct_stat.st_mode)) {
            std::ifstream fin(path);
            if(fin.is_open()) {
                std::istreambuf_iterator<char> begin(fin), end;
                str.assign(begin, end);
            }
            fin.close();
        }
        return str;
    }

    std::string SearchIndex(const std::string& path) {
        std::vector<std::string> index_files = {
            "index.html",
            "index.htm"
        };

        bool flag = (path == "/");
        for(auto index : index_files) {
            std::string index_path = path + (flag ? "" : "/") + index;

            // check existence
            struct stat struct_stat;
            if(::stat(index_path.c_str(), &struct_stat) == -1) {
                std::cerr << ::strerror(errno) << std::endl;
                continue;
            }
            // check type
            if(S_ISREG(struct_stat.st_mode)) {
                return index_path;
            }
        }
        return std::string();
    }

    void DefaultListener(HttpdImpl* phttpd, const Request& request) {
        Response response;
        // if request is invalid
        if(!request.Valid()) {
            response.SetStatusCode(StatusCodeEnum::kBadRequest);
            phttpd->Respond(response);
            return;
        }

        // request is valid
        switch(request.Method()) {
            case Request::MethodEnum::GET: {
                std::string str_uri = phttpd->GetHttpRootDir() + AdjustURI(request.URI());
                std::cout << str_uri << std::endl;
                // check type of uri
                struct stat struct_stat;
                if(::stat(str_uri.c_str(), &struct_stat) == -1) {
                    std::cerr << ::strerror(errno) << std::endl;
                    
                    // no such file or directory
                    phttpd->Respond(GetWelcomeResponse());
                    return;
                    response.SetStatusCode(StatusCodeEnum::kNotFound);
                    phttpd->Respond(response);
                    return;
                }

                std::string msg;
                // if URI required is a directory
                if(S_ISDIR(struct_stat.st_mode)) {
                    auto index_path = SearchIndex(str_uri);
                    
                    // find index files
                    if(!index_path.empty()) {
                        msg = ReadFile(index_path);
                    } else {
                        phttpd->Respond(GetWelcomeResponse());
                        return;
                        // response.SetStatusCode(StatusCodeEnum::kInternalServerError);
                        // phttpd->Respond(response);
                        // return;
                    } 
                } else if(S_ISREG(struct_stat.st_mode)) {
                    msg = ReadFile(str_uri);
                }
                
                // treat msg according to fields of reqeust.
                response.SetMessageBody(CompressGzip(msg));
                response.WriteField("Content-Encoding", "gzip");
                std::string extension = GetExtension(str_uri);
                if(IsImage(extension)) {
                    std::string content_type = ToLower(extension);
                    if(content_type == "jpg") {
                        content_type = "jpeg";
                    } else if(content_type == "ico") {
                        content_type = "x-icon";
                    }
                    response.WriteField("Content-Type", "image/" + content_type);
                }

                phttpd->Respond(response);
                return;
            }

            case Request::MethodEnum::POST:
                break;
        }
    }

    std::vector<std::string> Split(const std::string& str, char separator) {
        std::string tmp;
        std::vector<std::string> res;
        for(auto chr : str) {
            if(chr == separator) {
                res.push_back(tmp);
                tmp = "";
            } else {
                tmp += chr;
            }
        }
        res.push_back(tmp);
        return res;
    }

    Response GetWelcomeResponse() {
        Response response;
        std::string welcome_content = ReadFile("welcome/index.html");
        if(!welcome_content.empty()) {
            response.SetMessageBody(welcome_content);
        } else {
            response.SetStatusCode(StatusCodeEnum::kNotFound);
        }
        return response;
    }

}
}