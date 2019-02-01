#ifndef RESPONSE_H
#define RESPONSE_H

#include <map>
#include <vector>
#include <string>

namespace tri {

namespace http {

    enum StatusCodeEnum {
        kContinue = 100,
        kSwitchProtocols = 101,
        kOK = 200,
        kCreated = 201,
        kAccepted = 202,
        kNonAuthInfo = 203,
        kNoContent = 204,
        kResetContent = 205,
        kPartialContent = 206,
        kMultipleChoices = 300,
        kMovedPermanently = 301,
        kFound = 302,
        kSeeOther = 303,
        kNotModified = 304,
        kUseProxy = 305,
        kTemporaryRedirect = 307,
        kBadRequest = 400,
        kUnauthorized = 401,
        kPaymentRequired = 402,
        kForbidden = 403,
        kNotFound = 404,
        kMethodNotAllowed = 405,
        kNotAcceptable = 406,
        kProxyAuthRequired = 407,
        kRequestTimeout = 408,
        kConflict = 409,
        kGone = 410,
        kLengthRequired = 411,
        kPreconditionFailed = 412,
        kRequestEntityTooLarge = 413,
        kRequestURITooLong = 414,
        kUnsupportedMediaType = 415,
        kReqeustedRangeNotSatisfaiable = 416,
        kExpectionFailed = 417,
        kInternalServerError = 500,
        kNotImplemented = 501,
        kBadGatewey = 502,
        kServiceUnavailable = 503,
        kGateweyTimeout = 504,
        kHTTPVersionNotSupported = 505
    };

    const std::map<int, std::string> ReasonPhrase = {
        { 100, "Continue" },
        { 101, "Switching Protocols" },
        { 200, "OK" },
        { 201, "Created" },
        { 202, "Accepted" },
        { 203, "Non-Authoritative Infomation" },
        { 204, "No Content" },
        { 205, "Partial Content" },
        { 300, "Multiple Choices"},
        { 301, "Moved Permantently" },
        { 302, "Found" },
        { 303, "See Other" },
        { 304, "Not Modified" },
        { 305, "Use Proxy" },
        { 307, "Temporary Redirect" },
        { 400, "Bad Request" },
        { 401, "Unauthorized" },
        { 402, "Payment Required" },
        { 403, "Forbidden" },
        { 404, "Not Found" },
        { 405, "Method Not Allowed" },
        { 406, "Not Acceptable" },
        { 407, "Proxy Authentication Required" },
        { 408, "Request Timeout" },
        { 409, "Conflict" },
        { 410, "Gone" },
        { 411, "Length Required" },
        { 412, "Precondition Failed" },
        { 413, "Request Entity Too Large" },
        { 414, "Request-URI Too Long" },
        { 415, "Unsupported Media Type" },
        { 416, "Requested Range Not Satisfiable" },
        { 417, "Expectation Failed" },
        { 500, "Internal Server Error" },
        { 501, "Not IMplemented" },
        { 502, "Bad Gateway" },
        { 503, "Service Unavailable" },
        { 504, "Gateway Timeout" },
        { 505, "HTTP Version Not Supported" }
    };

    class Response {
    public:
        typedef std::vector<std::pair<std::string, std::string>> field_type;
        typedef field_type::iterator iterator;
        typedef field_type::const_iterator const_iterator;

        Response();
        
        std::string Policy() const;
        StatusCodeEnum StatusCode() const;
        std::string MessageBody() const;
        std::string Str() const;
        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;
        
        void SetStatusCode(StatusCodeEnum);
        Response& WriteField(std::pair<std::string, std::string>&& field);
        Response& WriteField(const std::string& field_name, const std::string field_value);
        void SetMessageBody(const std::string& msg);
        void SetMessageBody(std::string&& msg);

    private:
        std::string policy_;
        StatusCodeEnum status_code_;
        std::vector<std::pair<std::string, std::string>> headers_;
        std::string message_body_;
    };


    Response GetGeneralResponse();
}
}


#endif

