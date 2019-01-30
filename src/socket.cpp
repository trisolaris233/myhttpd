#include "socket.h"
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>

namespace tri {


tcpsocket::tcpsocket() :
    listenfd(0),
    buffer_size(DefaultBufferSize),
    buffer(NULL),
    _status(Status::Inactive)
{ 
}

bool tcpsocket::create(unsigned int port, const char* ip) {
    if(_status == Status::Active) return false;
    listenfd = socket(AF_INET, SOCK_STREAM, 0); // create socket

    // bind up ip and port
    sockaddr.sin_family = AF_INET;
    if(ip == NULL)
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        sockaddr.sin_addr.s_addr = inet_addr(ip);
    sockaddr.sin_port = htons(port);

    if(bind(listenfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) != 0)
        return false;

    return true;
}

unsigned int tcpsocket::buffersz() const {
    return buffer_size;
}

tcpsocket::Status tcpsocket::status() const {
    return _status;
}

bool tcpsocket::set_buffersz(unsigned int sz) {
    if(_status == Status::Inactive) {
        buffer_size = sz;
        return true;
    }
    return false;
}


void tcpsocket::listen(std::function<void(tcpsocket*, const char*)> receiver) {
    int connfd = 0, n = 0;
    // alloc memories for buffer
    buffer = static_cast<char*>(::malloc(buffer_size));
    // set the socket status
    _status = Status::Active;
    ::listen(listenfd, 1024);
    for(;;) {
        if((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1) {
            std::cout << "error\n" << std::endl;
            continue;
        }
        n = recv(connfd, buffer, buffer_size, 0);
        buffer[n] = '\0';
        receiver(this, buffer);
        ::close(connfd);
    }
}


void tcpsocket::close() {
    ::close(listenfd);
    _status = Status::Inactive;
}

bool tcpsocket::send(const std::string& msg) {
    if(_status == Status::Active) {
       if(::send(listenfd, msg.c_str(), msg.size(), 0) == -1)
          return false;
      return true;
    }
   return false; 
}
}
