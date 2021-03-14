#include "mbed.h"
#include <string>
#include "OLEDDisplay.h"
#include "http_request.h"
#include "MbedJSONValue.h"
#include "src/shared/PrintUtils.cpp"
#include "src/service/HttpService.cpp"
#include "config.cpp"


OLEDDisplay oled(MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL);
HttpService httpService(WIFI_SSID, WIFI_PASSWORD);

int main() {    
    /*
        GET EXAMPLE
    */
    HttpOptions* options = new HttpOptions();
    options->addHeader("my_header", "yeet");
    options->addQueryParam("param", "lalalal");

    MbedJSONValue response = httpService.get("http://192.168.1.103:8080/api/test/custom", options);
            
    std::string text = response["text"].get<std::string>();
    int number  = response["number"].get<int>();

    PrintUtils::print("text: ", text);
    PrintUtils::print("number: ", number);

    /*
        POST EXAMPLE
    */
    MbedJSONValue response1 = httpService.post("http://192.168.1.103:8080/api/test/custom", "{\"text\": \"my cool text\", \"number\": 120}");
            
    std::string text1 = response1["text"].get<std::string>();
    int number1  = response1["number"].get<int>();

    PrintUtils::print("text1: ", text1);
    PrintUtils::print("number1: ", number1);

    
    while(true) {
        thread_sleep_for(10000);
    }
}
