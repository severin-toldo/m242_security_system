#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include "config.cpp"
#include "MFRC522.h"
#include "src/shared/StringUtils.cpp"
#include "src/shared/PrintUtils.cpp"
#include "src/shared/CommonUtils.cpp"
#include "src/model/RFIDData.cpp"
#include "mbed.h"
#pragma once


class RFIDReaderService {

    private: MFRC522* rfidReader;


    public: RFIDReaderService() {
        rfidReader = new MFRC522(MBED_CONF_IOTKIT_RFID_MOSI, MBED_CONF_IOTKIT_RFID_MISO, MBED_CONF_IOTKIT_RFID_SCLK, MBED_CONF_IOTKIT_RFID_SS, MBED_CONF_IOTKIT_RFID_RST); 
        rfidReader->PCD_Init();
    }

    public: RFIDData* getRFIDData() {
        if (rfidReader->PICC_IsNewCardPresent()) {
            if (rfidReader->PICC_ReadCardSerial()) {
                std::string uuid = "";

                for (int i = 0; i < rfidReader->uid.size; i++) {
                    std::string uuidPart = CommonUtils::decimalToHex(rfidReader->uid.uidByte[i]);
                    
                    if (i == 0) {
                        uuid = "" + uuidPart;
                    } else {
                        uuid = uuid + ":" + uuidPart;
                    }                    
                }

                int type = rfidReader->PICC_GetType(rfidReader->uid.sak);
                std::string typeName = rfidReader->PICC_GetTypeName(type);
                
                RFIDData* rfidData = new RFIDData();
                rfidData->setRfidUUID(uuid);
                rfidData->setType(type);
                rfidData->setTypeName(typeName);
                
                return rfidData;
            }
        }

        return NULL;   
    }
};