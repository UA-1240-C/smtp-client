#ifndef ACCESSTOKENFETCHER_H
#define ACCESSTOKENFETCHER_H

#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <json/json.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
using tcp = asio::ip::tcp;

const std::string BASE_URL = "https://accounts.google.com/o/oauth2/auth";
const std::string SCOPE = "https://mail.google.com/";
const std::string RESPONSE_TYPE = "code";
const std::string ACCESS_TYPE = "offline";
const std::string PROMPT = "consent";
const std::string REDIRECT_URI = "http://localhost:8000/callback";
const std::string CLIENT_ID = "570952853562-5n34bmhjdsd6q7bovgf1g8ks6q6d930o.apps.googleusercontent.com";
const std::string CLIENT_SECRET = "R09DU1BYLVBLdTRfZE9FVURzWlA5TE5mUXZWenNtVG9RQmgK";
const std::string GRANT_TYPE = "authorization_code";
const std::string OAUTH_HOST = "oauth2.googleapis.com";
const std::string TOKEN_ENDPOINT = "/token";

class AccessTokenFetcher {
public:
    AccessTokenFetcher();
    ~AccessTokenFetcher();

    int FetchAccessToken();
    void set_authorization_code(const std::string& authorization_code);
    std::string get_access_token() const;

private:
    std::string m_authorization_code;
    std::string m_access_token;

    std::string UrlEncode(const std::string& value) const;
    void HandleRequest(tcp::socket& socket);
    int OpenOAuthBrowser() const;
    std::string ParseAccessToken(const std::string& json_response) const;
    void ExchangeCodeForToken(const std::string& authorization_code);
};

#endif //ACCESSTOKENFETCHER_H

