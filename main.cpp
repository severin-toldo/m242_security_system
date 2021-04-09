#include "mbed.h"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <string>
#include "http_request.h"
#include "MbedJSONValue.h"
#include "src/shared/PrintUtils.cpp"
#include "src/service/HttpService.cpp"
#include "src/service/OLEDDisplayService.cpp"
#include "src/service/RFIDReaderService.cpp"
#include "src/service/SecuritySystemService.cpp"
#include "src/service/UserButtonService.cpp"
#include "src/service/CountdownService.cpp"
#include "src/service/ToFSensorService.cpp"
#include "src/model/RFIDData.cpp"
#include "config.cpp"


int main() {
    PrintUtils::print("----------------------------------------------------------");
    PrintUtils::print("Defined Configs:");
    PrintUtils::print("WIFI_SSID: ", WIFI_SSID);
    PrintUtils::print("WIFI_PASSWORD: ", WIFI_PASSWORD);
    PrintUtils::print("API_BASE_URL: ", API_BASE_URL);
    PrintUtils::print("SECURITY_SYSTEM_ID: ", SECURITY_SYSTEM_ID);
    PrintUtils::print("SECURITY_SYSTEM_AUTH_TOKEN: ", SECURITY_SYSTEM_AUTH_TOKEN);
    PrintUtils::print("----------------------------------------------------------");
    PrintUtils::print();

    OLEDDisplayService* oledDisplayService = new OLEDDisplayService("Starting Security System...");
    oledDisplayService->clear();

    RFIDReaderService* rfidReaderService = new RFIDReaderService();
    UserButtonService* userButtonService = new UserButtonService();
    HttpService* httpService = new HttpService(WIFI_SSID, WIFI_PASSWORD);
    SecuritySystemService* securitySystemService = new SecuritySystemService(httpService);
    CountdownService* countdownService = new CountdownService(oledDisplayService);
    ToFSensorService* toFSensorService = new ToFSensorService();

    bool changed = true;
    while (true) {
       if (securitySystemService->getIsPaired()) {
           SecurityStatus status = securitySystemService->getStatus();

           if(changed) {
               oledDisplayService->print(CommonUtils::enum_to_string(status));
               oledDisplayService->printImageRight(CommonUtils::enum_to_image(status));
               changed = false;
           }

           if (status == SecurityStatus::ACTIVATED) {
               printf("hello\n");
               if(!toFSensorService->isInRange()) {
                   printf("Alarmed\n");
                   securitySystemService->activateAlarm();
               }   
           }
           
           if(status == SecurityStatus::ALARM) {
               if(securitySystemService->shouldSendAlarm()) {
                    securitySystemService->sendAlarm();
                    //TODO: DUMMY CODE
                    while (securitySystemService->getStatus() == SecurityStatus::ALARM) {
                        thread_sleep_for(1000);
                    }
                }
           }

           RFIDData* rfidData = rfidReaderService->getRFIDData();
           if (rfidData) {
               SecurityStatus newStatus = securitySystemService->changeStatus(rfidData->getRfidUUID());
               changed = newStatus != status;
               if(changed) {
                    countdownService->begin(20);    
               }
           }

       } else {
           oledDisplayService->print("Press User Button to start pairing.");

           if (userButtonService->isButtonPressed()) {
               oledDisplayService->print("Start Pairing...");
               
               std::string pairingCode = securitySystemService->startPairing();
               
               oledDisplayService->print("Pairing Code:\n" + pairingCode + "\nPlease restart the device now.");
               oledDisplayService->print(pairingCode);

               return 0;
           }
       }

        thread_sleep_for(200);
    }
}
