#include "src/service/OLEDDisplayService.cpp"
#include "src/service/HttpService.cpp"
#include <string>
#include "config.cpp"
#include "src/model/HttpOptions.cpp"
#include "src/shared/Urls.cpp"
#include "src/shared/CommonUtils.cpp"
#pragma once


class SecuritySystemService {

    private: HttpService* httpService;
    private: std::string status = "DEACTIVATED"; // ACTIVATED || DEACTIVATED
    private: bool isPaired = false;


    public: SecuritySystemService(HttpService* httpService) {
        this->httpService = httpService;
        setIsPaired();
    }

    public: std::string getStatus() {
        return status;
    }

    public: std::string changeStatus(std::string userRfidUUID) {
        std::string newStatus = status == "ACTIVATED" ? "DEACTIVATED" : "ACTIVATED";

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

    private: bool addHistory(std::string type, std::string userRfidUUID) {
        HttpOptions* options = new HttpOptions();
        options->addHeader("auth_token", SECURITY_SYSTEM_AUTH_TOKEN);

        MbedJSONValue body;
        body["type"] = type;
        body["userRfidUUID"] = userRfidUUID;

        std::string response = httpService->post(Urls::addSecuritySystemHistoryUrl(SECURITY_SYSTEM_ID), body.serialize(), options);
        
        return CommonUtils::stringToBoolean(response);
    }
};