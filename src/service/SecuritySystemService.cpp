#include "src/service/OLEDDisplayService.cpp"
#include "src/service/HttpService.cpp"
#include <string>
#pragma once


class SecuritySystemService {

    private: HttpService* httpService;
    private: std::string status = "DEACTIVATED"; // ACTIVATED || DEACTIVATED


    public: SecuritySystemService(HttpService* httpService) {
        this->httpService = httpService;
    }

    public: std::string getStatus() {
        return status;
    }

    public: std::string changeStatus() {
        status = status == "ACTIVATED" ? "DEACTIVATED" : "ACTIVATED";
        return status;
    }
};