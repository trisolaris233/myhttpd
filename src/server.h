#include "socket.h"


namespace tri {

class httpd_base {
public:
    httpd_base();
    virtual ~httpd_base();


protected:
    void start();
    
private:
    tcpsocket _socket;
};



class httpd_impl {
public:
    httpd_impl();
    virtual ~httpd_impl();


public:
    void start();
};




}
