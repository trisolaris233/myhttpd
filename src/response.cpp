#include "response.h"
#include <sstream>

namespace tri {

namespace http {

Response::Response():
    policy_("HTTP/1.1"),
    status_code_(StatusCodeEnum::kOK) {
}

std::string Response::Policy() const {
    return policy_;
}

StatusCodeEnum Response::StatusCode() const {
    return status_code_;
}

std::string Response::MessageBody() const {
    return message_body_;
}

std::string Response::Str() const {
    std::string str_res = "HTTP/1.1", str_space = " ", str_crlf = "\r\n";
    std::stringstream ss;
    int i_status_code = static_cast<int>(status_code_);
    ss << i_status_code;
    std::string str_status_code = ss.str(),
                str_reason_phrase = ReasonPhrase.at(i_status_code);
    
    str_res.append(str_space).append(str_status_code).append(str_space).append(str_reason_phrase).append(str_crlf);
    
    for(auto field : headers_) {
        str_res.append(field.first).append(":").append(field.second).append(str_crlf);
    }
    str_res.append(str_crlf).append(message_body_);
    return str_res;
}

Response::iterator Response::begin() {
    return headers_.begin();
}

Response::iterator Response::end() {
    return headers_.end();
}

Response::const_iterator Response::cbegin() const {
    return headers_.cbegin();
}

Response::const_iterator Response::cend() const {
    return headers_.cend();
}

void Response::SetStatusCode(StatusCodeEnum status_code) {
    status_code_ = status_code;
}

Response& Response::WriteField(std::pair<std::string, std::string>&& field) {
    headers_.push_back(field);
    return *this;
}

Response& Response::WriteField(const std::string& field_name, const std::string field_value) {
    headers_.push_back(std::make_pair(field_name, field_value));
    return *this;
}

void Response::SetMessageBody(const std::string& msg) {
    message_body_ = msg;
}



}

}
