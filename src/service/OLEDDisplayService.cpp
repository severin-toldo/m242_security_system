#include <string>
#include "config.cpp"
#include "OLEDDisplay.h"
#include "src/shared/StringUtils.cpp"
#include "mbed.h"
#pragma once


class OLEDDisplayService {

    private: OLEDDisplay* oledDisplay;


    public: OLEDDisplayService() {
        oledDisplay = new OLEDDisplay(MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL);

        oledDisplay->clear();
    }

    public: void print(std::string message) {
        oledDisplay->printf(StringUtils::concat(message, "\n").c_str());
    }

    public: void cursor(int16_t y, int16_t x) {
        oledDisplay->cursor(y, x);
    }
};
