#include "request.h"

namespace tri {

namespace http {

    Request::Request(const std::string& str) :
        method_(OPTIONS),
        URI_(""),
        policy_("HTTP//1.1"),
        valid_(false)
    {
        if(str.empty()) {
            return;
        }
        
         
        
    }

    Request::MethodEnum Request::Method() const {
        return method_;
    }

    std::string Request::Policy() const {
        return policy_;
    }

    Request::iterator Request::begin() {
        return fields_.begin();
    }

    Request::iterator Request::end() {
        return fields_.end();
    }

    Request::const_iterator Request::cbegin() const {
        return fields_.cbegin();
    }

    Request::const_iterator Request::cend() const {
        return fields_.cend();
    }

    std::string Request::URI() const {
        return URI_;
    }

    bool Request::Valid() const {
        return valid_;
    }

}

}

