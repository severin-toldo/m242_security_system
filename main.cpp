#include "mbed.h"
#include <string>
#include "OLEDDisplay.h"
#include "http_request.h"
#include "MbedJSONValue.h"
#include "src/shared/PrintUtils.cpp"
#include "src/service/HttpService.cpp"
#include "src/service/SecuritySystemHistoryService.cpp"
#include "config.cpp"


OLEDDisplay oled(MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL);

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

    HttpService* httpService = new HttpService(WIFI_SSID, WIFI_PASSWORD);
    SecuritySystemHistoryService* securitySystemHistoryService = new SecuritySystemHistoryService(httpService);




    SecuritySystemHistoryCreateRequest sshcr;
    sshcr.setType("ACTIVATED");
    sshcr.setDatetime("2021-03-14T14:42:23-0000"); // TODO
    sshcr.setUserRfidUUID("a3:6b:c8:j9"); // TODO

    bool res = securitySystemHistoryService->addHistory(SECURITY_SYSTEM_AUTH_TOKEN, SECURITY_SYSTEM_ID, sshcr);












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
    
    while(true) {
        thread_sleep_for(10000);
    }
}
