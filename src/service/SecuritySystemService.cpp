#include "src/service/OLEDDisplayService.cpp"
#include "src/service/HttpService.cpp"
#include "src/shared/SecurityStatus.cpp"
#include <chrono>
#include <ctime>
#include <string>
#include "config.cpp"
#include "src/model/HttpOptions.cpp"
#include "src/shared/Urls.cpp"
#include "src/shared/CommonUtils.cpp"
#pragma once

class SecuritySystemService {

    private: HttpService* httpService;
    private: SecurityStatus status = DEACTIVATED;
    private: time_t lastChanged = CommonUtils::getCurrentTime();
    private: bool isPaired = false;


    public: SecuritySystemService(HttpService* httpService) {
        this->httpService = httpService;
        setIsPaired();
    }

    public: SecurityStatus getStatus() {
        return status;
    }

    public: SecurityStatus changeStatus(std::string userRfidUUID) {
        SecurityStatus newStatus = status >= 1 ? DEACTIVATED : ACTIVATED;

        if (addHistory(newStatus, userRfidUUID)) {
            status = newStatus;
            lastChanged = CommonUtils::getCurrentTime();
        }

        return status;
    }

    public: void activateAlarm() {
        status = SecurityStatus::ALARM;
        lastChanged = CommonUtils::getCurrentTime();
    }

    public: bool shouldSendAlarm() {
        return status == SecurityStatus::ALARM 
            && CommonUtils::getDurationSeconds(lastChanged, CommonUtils::getCurrentTime()) >= 20;
    }

    public: bool sendAlarm() {
        if (addHistory(SecurityStatus::ALARM, "SYSTEM")) {
            status = SecurityStatus::ALARM;
            lastChanged = CommonUtils::getCurrentTime();
            return true;
        }

        return false;
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