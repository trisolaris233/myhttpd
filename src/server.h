#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include <memory>
#include <vector>
#include <functional>

namespace tri {

namespace http {


class Response;
class Request;

class HttpdBase {
public:
    virtual ~HttpdBase() = 0;

    virtual void Start() {}
    virtual void Respond(const Response& response) {}

};

class HttpdImpl : public HttpdBase {
public:
    typedef std::function<void(HttpdImpl*, const Request&)> listener_type;
    
    HttpdImpl(unsigned int port, const char* ip = NULL);
    ~HttpdImpl() {}

public:
    void SetHttpRootDir(const std::string& dir);
    void SetListener(listener_type listener);
    std::string GetHttpRootDir() const;
    virtual void Start();
    virtual void Respond(const Response& response);

private:
    std::string root_dir_;
    TcpSocket socket_;
    listener_type listener_;

};

// helper functions
bool IsImage(const std::string& extension);
std::string GetExtension(const std::string& uri);
std::string AdjustURI(const std::string& uri);
std::string ReadFile(const std::string& path);
std::string SearchIndex(const std::string& path);
void DefaultListener(HttpdImpl* phttpd, const Request& request);
std::vector<std::string> Split(const std::string& str, char separator);
Response GetWelcomeResponse();

}
}
#endif
