#include "socket.h"
#include "parse.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <functional>
#include <unistd.h>
#include "request.h"
#include <sstream>

void echo(tri::TcpSocket* psocket, const char* msg) {
  ::puts(msg);  
} 

void httparse(tri::TcpSocket* psocket, const char* msg) {
    std::cout << "httprase is called" << std::endl;
    auto res_lines = tri::parse::ParseRequestToLines(msg);
    for(auto line : res_lines) {
        std::cout << line << std::endl;
    } 
}

void httpraseplus(tri::TcpSocket* psocket, const char* msg) {
    std::cout << "httpraseplus is called" << std::endl;
    auto res = tri::parse::ParseRequest(tri::parse::ParseRequestToLines(msg));
    std::cout << "size of desc is " << res.second.size() << std::endl;    
}

void httpraseplus2(tri::TcpSocket* psocket, const char* msg) {
    tri::http::Request request(msg);
    std::cout << request.Valid() << std::endl;
    std::cout << static_cast<int>(request.Method()) << std::endl;
    std::cout << request.URI() << std::endl;

    for(auto itr = request.begin(); itr != request.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
    }
}

int main(int argc, char** argv) {
    tri::TcpSocket* psocket = new tri::TcpSocket();
    std::stringstream ss(argv[1]);
    int port;
    ss >> port;
    psocket->Create(port);
    psocket->Listen(httpraseplus2);
    return 0;
}
