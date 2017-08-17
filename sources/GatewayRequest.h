#pragma once

#include "json/json.h"
#include <httpd.h>
#include <string>
namespace ssorest
{
    class GatewayRequest
    {
    private:
        const server_rec* server;
        std::string scheme;
        Json::Value jsonData;
    public:
        GatewayRequest(request_rec* sourceRequest);
        const Json::Value& getPayload() const;
        std::string sendTo(const std::string& gatewayUrl) const;
        void setAcoName(const std::string& value);
        void setPluginId(const std::string& value);
    private:
        static std::string getScheme(const request_rec* request);
        static int getServerPort(const request_rec* request);
        void verifyThatSourceRequestIsDefined() const;
        bool isSecureProtocol() const;
        
    };
}