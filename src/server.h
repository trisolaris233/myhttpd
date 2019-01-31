#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include "request.h"
#include "response.h"
#include <memory>
#include <functional>

namespace tri {

namespace http {
class httpd_base {
public:
    httpd_base();
    virtual ~httpd_base();


protected:
    void Start();
    void Respond(const Response& response); 
};



class httpd_impl : public httpd_base {
public:
    httpd_impl();
    virtual ~httpd_impl();


public:
    void start(std::function<void(httpd_base*)> receiver);


private:
    TcpSocket socket_;

};
}

}
#endif
