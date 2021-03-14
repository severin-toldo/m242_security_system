#include <string>
#include "config.cpp"
#include "src/shared/StringUtils.cpp"
#pragma once


class Urls {
    public: static std::string addSecuritySystemHistoryUrl(int securitySystemId) {
        return StringUtils::concat(API_BASE_URL, "/api/security-system/", to_string(securitySystemId), "/history");        
    }
};