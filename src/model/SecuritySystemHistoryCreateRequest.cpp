#include <string>
#pragma once


class SecuritySystemHistoryCreateRequest {
    private: std::string datetime;
    private: std::string type; // ACTIVATED || DEACTIVATED || ALARM
    private: std::string userRfidUUID;


    public: std::string getDatetime() {
        return datetime;
    }

    public: void setDatetime(std::string datetime) {
        this->datetime = datetime;
    }

    public: std::string getType() {
        return type;
    }

    public: void setType(std::string type) {
        this->type = type;
    }

    public: std::string getUserRfidUUID() {
        return userRfidUUID;
    }

    public: void setUserRfidUUID(std::string userRfidUUID) {
        this->userRfidUUID = userRfidUUID;
    }
};

