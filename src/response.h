#ifdef _RESPONSE_H
#define _RESPONSE_H 

namespace tri {

namespace http {

union StatusCodeEnum {
    enum InformationEnum {
        kContinue = 100,
        kSwitchProtocols = 101
    };
    enum SuccessfulEnum {
        kOK = 200,
        kCreated = 201,
        kAccepted = 202,
        kNonAuthInfo = 203,
        kNoContent = 204,
        kResetContent = 205,
        kPartialContent = 206
    };
    enum RedirectionEnum {
        kMultipleChoices = 300,
        kMovedPermanently = 301,
        kFound = 302,
        kSeeOther = 303,
        kNotModified = 304,
        kUseProxy = 305,
        kTemporaryRedirect = 307
    };
    enum ClientErrorEnum
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
    enum ServerErrorEnum {
        kInternalServerError = 500,
        kNotImplemented = 501,
        kBadGatewey = 502,
        kServiceUnavailable = 503,
        kGateweyTimeout = 504,
        kHTTPVersionNotSupported = 505
    };
    SuccessfulEnum success_code;
    RedirectionEnum redirection_code;
    ClientErrorEnum client_error_code;
    ServerErrorEnum server_error_code;
};


class Response {
public:
    typedef std::vector<std::pair<std::string, std::string>> field_type;
    typedef field_type::iterator iterator;
    typedef field_type::const_iterator const_iterator;

    Response();
    
    std::string Policy() const;
    Method Method() const;
    StatusCodeEnum StatusCode() const;
    std::string MessageBody() const;
    iterator begin() const;
    iterator end() const;
    const_iteartor cbegin() const;
    const_iterator cend() const;
    
    Response& WriteField(std::pair<std::string, std::string>&& field);

private:
    std::string policy_;
    StatusCodeEnum status_code_;
    field_type headers_;
    std::string message_body_;
};

}
} 


#endif
