#include "socket.h"
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>

namespace tri {


TcpSocket::TcpSocket() :
    listenfd_(0),
    buffer_size_(DefaultBufferSize),
    buffer_(NULL),
    status_(StatusEnum::Inactive)
{ 
}

bool TcpSocket::Create(unsigned int port, const char* ip) {
    if(status_ == StatusEnum::Active) return false;
    listenfd_ = socket(AF_INET, SOCK_STREAM, 0); // create socket

    // bind up ip and port
    socket_address_.sin_family = AF_INET;
    if(ip == NULL)
        socket_address_.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        socket_address_.sin_addr.s_addr = inet_addr(ip);
    socket_address_.sin_port = htons(port);

    if(bind(listenfd_, (struct sockaddr*)&socket_address_, sizeof(sockaddr)) != 0)
        return false;

    return true;
}

unsigned int TcpSocket::BufferSize() const {
    return buffer_size_;
}

TcpSocket::StatusEnum TcpSocket::Status() const {
    return status_;
}

bool TcpSocket::SetBufferSize(unsigned int sz) {
    if(status_ == StatusEnum::Inactive) {
        buffer_size_ = sz;
        return true;
    }
    return false;
}


void TcpSocket::Listen(std::function<void(TcpSocket*, const char*)> receiver) {
    int connfd = 0, n = 0;
    // alloc memories for buffer
    buffer_ = static_cast<char*>(::malloc(buffer_size_));
    // set the socket status
    status_ = StatusEnum::Active;
    ::listen(listenfd_, 1024);
    for(;;) {
        if((connfd = accept(listenfd_, (struct sockaddr*)NULL, NULL)) == -1) {
            std::cout << "error\n" << std::endl;
            continue;
        }
        n = recv(connfd, buffer_, buffer_size_, 0);
        buffer_[n] = '\0';
        receiver(this, buffer_);
        ::close(connfd);
    }
}


void TcpSocket::Close() {
    ::close(listenfd_);
    status_ = StatusEnum::Inactive;
}

bool TcpSocket::Send(const std::string& msg) {
    if(status_ == StatusEnum::Active) {
       if(::send(listenfd_, msg.c_str(), msg.size(), 0) == -1)
          return false;
      return true;
    }
   return false; 
}
}
