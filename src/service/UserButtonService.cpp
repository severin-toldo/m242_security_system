#include <string>
#include "config.cpp"
#include "OLEDDisplay.h"
#include "src/shared/StringUtils.cpp"
#include "mbed.h"
#pragma once


class UserButtonService {

    private: DigitalIn* userButton;


    public: UserButtonService() {
        userButton = new DigitalIn(BUTTON1);
    }

    public: bool isButtonPressed() {
        return userButton->read() == 0;
    }
};
