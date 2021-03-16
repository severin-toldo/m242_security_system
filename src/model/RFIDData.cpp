#include <string>
#pragma once


class RFIDData {

    private: std::string rfidUUID;
    private: int type;
    private: std::string typeName;


    public: std::string getRfidUUID() {
        return rfidUUID;
    }

    public: void setRfidUUID(std::string rfidUUID) {
        this->rfidUUID = rfidUUID;
    }

    public: int getType() {
        return type;
    }

    public: void setType(int type) {
        this->type = type;
    }

    public: std::string getTypeName() {
        return typeName;
    }

    public: void setTypeName(std::string typeName) {
        this->typeName = typeName;
    }
};