#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>
#include <sys/types.h>
#include <string>
#include <functional>
#include <memory>

namespace tri {

class TcpSocket {
    enum { Ipv4Size = 0xc };
    enum { DefaultBufferSize = 1024 };
    enum StatusEnum {
        Inactive,
        Active
    };
public:
    TcpSocket();
    
    bool Create(unsigned int port, const char* ip = NULL);
    unsigned int BufferSize() const;
    StatusEnum Status() const;
    bool SetBufferSize(unsigned int sz);

    void Listen(std::function<void(TcpSocket*, std::shared_ptr<char>)> receiver);
    void Close();
    bool Send(const std::string& msg);

private:
    int listenfd_;
    unsigned int buffer_size_;
    struct sockaddr_in socket_address_;
    std::shared_ptr<char> buffer_;
    StatusEnum status_;
    TcpSocket(const TcpSocket&) = delete;
    int connfd_;
};


}


#endif
