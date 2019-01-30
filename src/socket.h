#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <sys/types.h>
#include <string>
#include <functional>

namespace tri {

class tcpsocket {
    enum { Ipv4Size = 0xc };
    enum { DefaultBufferSize = 1024 };
    enum Status {
        Inactive,
        Active
    };
public:
    tcpsocket();
    
    bool create(unsigned int port, const char* ip = NULL);
    unsigned int buffersz() const;
    Status status() const;
    bool set_buffersz(unsigned int sz);

    void listen(std::function<void(tcpsocket*, const char*)> receiver);
    void close();
    bool send(const std::string& msg);
    
protected:
    bool is_valid();

private:
    int listenfd;
    unsigned int buffer_size;
    struct sockaddr_in sockaddr;
    char* buffer;
    Status _status;
    tcpsocket(const tcpsocket&) = delete;
};

/*
class httpd_base {
public:
    httpd_base(unsigned int port, const char* ip = NULL);
    virtual ~httpd_base();

protected:
    void start() const;

private:
    tcpsocket _socket;

};

class httpd : public httpd_base {
public:
    httpd(unsigned int port, const char* ip = NULL);
    virtual ~httpd();

    void start();
};
*/

}


#endif
