#include <string>
#pragma once

class CommonUtils {

    public: static std::string decimalToHex(uint8_t decimalValue) {
        char hexString[20];
        sprintf(hexString, "%02X", decimalValue);
        
        return hexString;
    }
};