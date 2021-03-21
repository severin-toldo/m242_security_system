#include "mbed.h"
#include <string>
#include "http_request.h"
#include "MbedJSONValue.h"
#include "src/shared/PrintUtils.cpp"
#include "src/service/HttpService.cpp"
#include "src/service/OLEDDisplayService.cpp"
#include "src/service/RFIDReaderService.cpp"
#include "src/service/SecuritySystemService.cpp"
#include "src/service/UserButtonService.cpp"
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
    RFIDReaderService* rfidReaderService = new RFIDReaderService();
    UserButtonService* userButtonService = new UserButtonService();
    HttpService* httpService = new HttpService(WIFI_SSID, WIFI_PASSWORD);
    SecuritySystemService* securitySystemService = new SecuritySystemService(httpService);
    
    while (true) {
       if (securitySystemService->getIsPaired()) {
           oledDisplayService->print(securitySystemService->getStatus());

           if (securitySystemService->getStatus() == "ACTIVATED") {
               // TODO alarm stuff
           }
           
           RFIDData* rfidData = rfidReaderService->getRFIDData();

           PrintUtils::print(rfidData->getRfidUUID());
           
           if (rfidData) {
               std::string status = securitySystemService->changeStatus(rfidData->getRfidUUID());
               oledDisplayService->print(status);
               thread_sleep_for(20000);
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

     
    















    // TODO move conf into service also oled etc creates service

    /*
   

    SecuritySystemHistoryCreateRequest sshcr;
    sshcr.setType("ACTIVATED");
    sshcr.setDatetime("2021-03-14T14:42:23-0000"); // TODO
    sshcr.setUserRfidUUID("a3:6b:c8:j9"); // TODO

    bool res = securitySystemHistoryService->addHistory(SECURITY_SYSTEM_AUTH_TOKEN, SECURITY_SYSTEM_ID, sshcr);
    */

    /*

    
        GET EXAMPLE
    
    HttpOptions* options = new HttpOptions();
    options->addHeader("my_header", "yeet");
    options->addQueryParam("param", "lalalal");

    MbedJSONValue response = httpService.get("http://192.168.1.103:8080/api/test/custom", options);
            
    std::string text = response["text"].get<std::string>();
    int number  = response["number"].get<int>();

    // PrintUtils::print("text: ", text);
    // PrintUtils::print("number: ", number);

    
        POST EXAMPLE
    
    MbedJSONValue body;
    body["text"] = "my cool text";
    body["number"] = 120;

    MbedJSONValue response1 = httpService.post("http://192.168.1.103:8080/api/test/customjsjsjsjsjsj", body.serialize());



            
    std::string text1 = response1["text"].get<std::string>();
    int number1  = response1["number"].get<int>();

    // PrintUtils::print("text1: ", text1);
    // PrintUtils::print("number1: ", number1);
    */
/*
     MbedJSONValue responseBodyAsJson;
            parse(responseBodyAsJson, httpResponse->get_body_as_string().c_str());*/
}
