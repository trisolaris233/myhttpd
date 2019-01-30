#ifdef RESPONSE_H
#define RESPONSE_H 

namespace tri {

namespace http {

union StatusCodeEnum {
    enum Successful {
        kOK = 200,
        kCreated = 201,
        kAccepted = 202,
        kNonAuthInfo = 203,
        kNoContent = 204,
        kResetContent = 205,
        kPartialContent = 206
    };
    enum Redirection {
        kMultipleChoices = 300,
        kMovedPermanently = 301,
        kFound = 302,
        kSeeOther = 303,
        kNotModified = 304,
        kUseProxy = 305,
        kTemporaryRedirect = 307
    };
    enum ClientError {
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
        kExpectionFailed = 417
    };
    enum ServerError {
        kInternalServerError = 500,
        kNotImplemented = 501,
        kBadGatewey = 502,
        kServiceUnavailable = 503,
        kGateweyTimeout = 504,
        kHTTPVersionNotSupported = 505
    };
    Successful success_code;
    Redirection redirection_code;
    ClientError client_error_code;
    ServerError server_error_code;
};


class Response {
public:
    typedef std::vector<std::pair<std::string, std::string>> field_type;
    typedef field_type::iterator iterator;
    typedef field_type::const_iterator const_iterator;

    Response();
    Response(const char* str);
    Response(std::string& str);
    
    std::string Policy() const;
    Method Method() const;
    StatusCodeEnum StatusCode() const;
    std::string MessageBody() const;
    iterator begin() const;
    iterator end() const;
    const_iteartor cbegin() const;
    const_iterator cend() const;

private:
    std::string policy_;
    StatusCodeEnum status_code_;
    field_type headers_;
    std::string message_body_;
};

}
} 


#endif
