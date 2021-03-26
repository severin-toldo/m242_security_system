#include <string>
#include "src/shared/SecurityStatus.cpp"
#include "src/shared/Images.h"
#pragma once

class CommonUtils {

    public: static std::string decimalToHex(uint8_t decimalValue) {
        char hexString[20];
        sprintf(hexString, "%02X", decimalValue);
        
        return hexString;
    }

    public: static std::string enum_to_string(SecurityStatus status) {
        switch (status) {
            case DEACTIVATED:
                return "DEACTIVATED";
            case ACTIVATED:
                return "ACTIVATED";
            case ALARM:
                return "ALARM";
            default:
                return "Invalid Status";
        }
    }

    public: static const unsigned char *enum_to_image(SecurityStatus status) {
        switch (status) {
            case DEACTIVATED:
                return Images::getLockOpen();
            case ACTIVATED:
            case ALARM:
                return Images::getLockClosed();
            default:
                return nullptr;
        }
    }
    
    public: static bool stringToBoolean(std::string stringValue) {
        return stringValue == "true" ? true : false;
    }
};