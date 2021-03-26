#include "src/service/OLEDDisplayService.cpp"
#include "src/service/HttpService.cpp"
#include "src/shared/SecurityStatus.cpp"
#include <string>
#pragma once


class SecuritySystemService {

    private: HttpService* httpService;
    private: SecurityStatus status = deactivated;


    public: SecuritySystemService(HttpService* httpService) {
        this->httpService = httpService;
    }

    public: SecurityStatus getStatus() {
        return status;
    }

    public: SecurityStatus changeStatus() {
        status = status == deactivated ? activated : deactivated;
        return status;
    }
};