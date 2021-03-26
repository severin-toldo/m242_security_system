#include "src/service/OLEDDisplayService.cpp"
#pragma once

class CountdownService {
    private: OLEDDisplayService *displayService;

    public: CountdownService(OLEDDisplayService *oLEDDisplayService) {
        displayService = oLEDDisplayService;
    }

    public: void begin(unsigned int seconds) {
        if(seconds < 1) {
            return;
        }

        char buff[100];
        while (seconds > 0) {
            snprintf(buff, sizeof(buff), "%d", seconds);
            displayService->print(buff);
            thread_sleep_for(1000);
            seconds--;
        }
    }
};