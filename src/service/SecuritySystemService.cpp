#include "src/service/OLEDDisplayService.cpp"
#include "src/service/HttpService.cpp"
#include "src/shared/SecurityStatus.cpp"
#include <string>
#include "config.cpp"
#include "src/model/HttpOptions.cpp"
#include "src/shared/Urls.cpp"
#include "src/shared/CommonUtils.cpp"
#pragma once


class SecuritySystemService {

    private: HttpService* httpService;
    private: SecurityStatus status = deactivated;
    private: bool isPaired = false;


    public: SecuritySystemService(HttpService* httpService) {
        this->httpService = httpService;
        setIsPaired();
    }

    public: SecurityStatus getStatus() {
        return status;
    }

    public: SecurityStatus changeStatus(std::string userRfidUUID) {
        SecurityStatus newStatus = status == deactivated ? activated : deactivated;

        if (addHistory(newStatus, userRfidUUID)) {
            status = newStatus; 
        }

        return status;
    }

    public: bool getIsPaired() {
        return isPaired;
    }

    private: void setIsPaired() {
        HttpOptions* options = new HttpOptions();
        options->addHeader("auth_token", SECURITY_SYSTEM_AUTH_TOKEN);

        std::string response = httpService->get(Urls::isPairedUrl(SECURITY_SYSTEM_ID), options);
        
        isPaired = CommonUtils::stringToBoolean(response);      
    }

    public: std::string startPairing() {
        HttpOptions* options = new HttpOptions();
        options->addHeader("auth_token", SECURITY_SYSTEM_AUTH_TOKEN);

        std::string response = httpService->post(Urls::startPairingUrl(SECURITY_SYSTEM_ID), NULL, options);
        
        return response;
    }

    private: bool addHistory(SecurityStatus type, std::string userRfidUUID) {
        HttpOptions* options = new HttpOptions();
        options->addHeader("auth_token", SECURITY_SYSTEM_AUTH_TOKEN);

        MbedJSONValue body;
        body["type"] = CommonUtils::enum_to_string(type);
        body["userRfidUUID"] = userRfidUUID;

        std::string response = httpService->post(Urls::addSecuritySystemHistoryUrl(SECURITY_SYSTEM_ID), body.serialize(), options);
        
        return CommonUtils::stringToBoolean(response);
    }
};