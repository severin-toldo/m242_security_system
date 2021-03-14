#define WIFI_SSID "LERNKUBE"
#define WIFI_PASSWORD "l3rnk4b3"


#include "src/shared/PrintUtils.cpp"


void printConfig() {
    PrintUtils::print("----------------------------------------------------------");
    PrintUtils::print("Defined Configs:");
    PrintUtils::print("WIFI_SSID: ", WIFI_SSID);
    PrintUtils::print("WIFI_PASSWORD: ", WIFI_PASSWORD);
    PrintUtils::print("----------------------------------------------------------");
    PrintUtils::print();
}