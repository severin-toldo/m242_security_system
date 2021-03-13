#include <cstdlib>
#include <iostream>
#include "mbed.h"
#include "src/shared/PrintUtils.cpp"
#include "src/shared/ExceptionUtils.cpp"
#pragma once

class HttpService {

    private: WiFiInterface* wifiInterface;


    public: HttpService(std::string ssid, std::string password) {
        wifiInterface = WiFiInterface::get_default_instance();

        if (!wifiInterface) {
            ExceptionUtils::throwException("No WiFiInterface found");
        }

        PrintUtils::print("Connecting to ", ssid);

        int connectionResponse = wifiInterface->connect(ssid.c_str(), password.c_str(), NSAPI_SECURITY_WPA_WPA2);

        if (connectionResponse != 0) {
            ExceptionUtils::throwException("Connection Error: ", connectionResponse);
        }

        SocketAddress socketAddress;
        wifiInterface->get_ip_address(&socketAddress);

        PrintUtils::print("Connecting Successful");
        PrintUtils::print("MAC: ", wifiInterface->get_mac_address());
        PrintUtils::print("IP: ", socketAddress.get_ip_address());        
    }

    // TODO http functions
};