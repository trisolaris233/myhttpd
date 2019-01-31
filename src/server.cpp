#include "server.h"
#include "request.h"
#include "response.h"
#include <memory>

namespace tri {
namespace http {

    HttpdBase::~HttpdBase() {}
    
    void HttpdImpl::SetListener(HttpdImpl::listener_type listener) {
        listener_ = listener;
    }

    HttpdImpl::HttpdImpl(unsigned int port, const char* ip) {
        socket_.Create(port, ip);
    }


    void HttpdImpl::Start() {
        socket_.Listen([=](tri::TcpSocket* psocket, std::shared_ptr<char> receiver) {
            listener_(this, Request(receiver.get()));
        });
    }

    void HttpdImpl::Respond(const Response& response) {
        socket_.Send(response.Str());
    }

}
}