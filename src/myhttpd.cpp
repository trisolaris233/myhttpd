#include "socket.h"
#include "parse.h"
#include "server.h"
#include "request.h"
#include "response.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <functional>
#include <unistd.h>
#include <sstream>
#include <memory>

void echo(tri::TcpSocket* psocket, const char* msg) {
  ::puts(msg);  
} 

void httparse(tri::TcpSocket* psocket, const char* msg) {
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

void httpraseplus2(tri::TcpSocket* psocket, std::shared_ptr<char> msg) {
    tri::http::Request request(msg.get());
    std::cout << request.Valid() << std::endl;
    std::cout << static_cast<int>(request.Method()) << std::endl;
    std::cout << request.URI() << std::endl;

    for(auto itr = request.begin(); itr != request.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
    }
}

// request receiver
void Responder(tri::http::HttpdBase* phttpd, const tri::http::Request& request) {
    tri::http::Response response;
    response.WriteField("Content-Type", "text/html; charset=utf=8");
    response.SetMessageBody("<html<title>Documention</title><body><h1>23333</h1></body></html>");
    phttpd->Respond(response);
}

int main(int argc, char** argv) {
    std::stringstream ss(argv[1]);
    int port;
    ss >> port;

    tri::http::HttpdBase* phttpd = new tri::http::HttpdImpl(port);
    static_cast<tri::http::HttpdImpl*>(phttpd)->SetListener(Responder);
    phttpd->Start();

    return 0;
}
