#include "request.h"
#include "parse.h"
#include <algorithm>

namespace tri {

namespace http {

    Request::Request(const std::string& str) :
        method_(OPTIONS),
        URI_(""),
        policy_("HTTP/1.1"),
        valid_(false)
    {
        if(str.empty()) {
            return;
        }

        auto res = std::move(tri::parse::ParseRequest(std::move(tri::parse::ParseRequestToLines(str.c_str()))));
        valid_ = res.first;
        if(valid_) {
            fields_ = res.second;
            URI_ = fields_[0].second;
            std::string str_method = fields_[0].first;
            std::vector<std::string> vtr_methods = {"OPTIONS", "GET", "POST", "HEAD"};
            method_ = static_cast<MethodEnum>(std::distance(vtr_methods.begin(), std::find(vtr_methods.begin(), vtr_methods.end(), fields_[0].first)) + 1);
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

    std::string Request::GetField(const std::string& field_name) const {
        for(auto field : fields_) {
            if(field.first == field_name) {
                return field.second;
            }
        }
        return std::string();
    }

}

}

