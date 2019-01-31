#ifndef REQUEST_H
#define REQUEST_H

#include <vector>
#include <string>

namespace tri {

namespace http {
class Request {
public:
    enum MethodEnum {
        OPTIONS = 1,
        GET,
        POST,
        HEAD
    };
    typedef std::vector<std::pair<std::string, std::string>> field_type;
    typedef field_type::iterator iterator;
    typedef field_type::const_iterator const_iterator;

    Request(const std::string& str);

    MethodEnum Method() const;
    std::string Policy() const;
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    std::string URI() const;
    bool Valid() const;

private:
    MethodEnum method_;
    std::string URI_;
    std::string policy_;
    std::vector<std::pair<std::string, std::string>> fields_;
    bool valid_;
};
}
}
#endif
