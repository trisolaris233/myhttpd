#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include <memory>
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
    typedef std::function<void(HttpdBase*, const Request&)> listener_type;
    
    HttpdImpl(unsigned int port, const char* ip = NULL);
    ~HttpdImpl() {}

public:
    void SetListener(listener_type listener);
    virtual void Start();
    virtual void Respond(const Response& response);

private:
    TcpSocket socket_;
    listener_type listener_;

};
}

}
#endif
