#include <string>
#include "config.cpp"
#include "src/shared/StringUtils.cpp"
#pragma once


class Urls {
    public: static std::string addSecuritySystemHistoryUrl(int securitySystemId) {
        return StringUtils::concat(API_BASE_URL, "/api/security-system/", to_string(securitySystemId), "/history");        
    }

    public: static std::string startPairingUrl(int securitySystemId) {
        return StringUtils::concat(API_BASE_URL, "/api/security-system/pair/", to_string(securitySystemId), "/start");        
    }

    public: static std::string isPairedUrl(int securitySystemId) {
        return StringUtils::concat(API_BASE_URL, "/api/security-system/pair/", to_string(securitySystemId), "/status");        
    }
};