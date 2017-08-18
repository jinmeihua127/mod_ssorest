#include "RequestHeaderWrapper.h"

namespace ssorest
{
    RequestHeaderWrapper::RequestHeaderWrapper(request_rec* r)
    : request(r)
    {

    }

    void RequestHeaderWrapper::propagateResponseHeader(const std::map<std::string, std::string>& sourceHeaders, TargetHeader targetHeader)
    {
        auto destinationHeader = (targetHeader == TargetHeader::In ? request->headers_in : request->headers_out);
        for (auto& sourceHeader : sourceHeaders)
        {
            auto& name = sourceHeader.first;
            auto& value = sourceHeader.second;
            ::apr_table_set(destinationHeader, name.c_str(), value.c_str());
        }
    }

    void RequestHeaderWrapper::propagateCookies(const std::map<std::string, std::string>& sourceCookies, TargetHeader targetHeader)
    {
        std::string mergedCookies;
        auto destinationHeader = (targetHeader == TargetHeader::In ? request->headers_in : request->headers_out);
        auto rawCurrentCookies = ::apr_table_get(destinationHeader, "Cookie");
        if (rawCurrentCookies)
            mergedCookies.assign(rawCurrentCookies);
        
        for (const auto& sourceCookie : sourceCookies)
        {
            if (!mergedCookies.empty())
                mergedCookies += "; ";
            mergedCookies += sourceCookie.first + "=" + sourceCookie.second;
        }
        ::apr_table_set(destinationHeader, "Cookie", mergedCookies.c_str());
    }
}