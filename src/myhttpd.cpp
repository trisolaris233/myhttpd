#include "socket.h"
#include "parse.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <functional>
#include <unistd.h>
void echo(tri::tcpsocket* psocket, const char* msg) {
  ::puts(msg);  
} 

void httparse(tri::tcpsocket* psocket, const char* msg) {
    std::vector<std::pair<std::string, std::string>> t;
    tri::parse::ParseRequest(msg, t);
    std::cout << "t.size() = " << t.size() << std::endl;

    for(auto pss : t) {
        std::cout << pss.first << " -> " << pss.second << std::endl;
    }
    ::sleep(1);
}

int main(int argc, char** argv) {
    tri::tcpsocket* psocket = new tri::tcpsocket();
    psocket->create(2333);
    psocket->listen(echo);
    return 0;
}
