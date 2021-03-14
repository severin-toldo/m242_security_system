#include <cstdlib>
#include <cstring>
#include <iostream>
#include "mbed.h"
#include "src/shared/PrintUtils.cpp"
#include "src/shared/ExceptionUtils.cpp"
#include "MbedJSONValue.h"
#include "http_request.h"
#include "src/model/HttpOptions.cpp"
#include <iterator>
#include <map>
#include <string>
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
        PrintUtils::print();      
    }

    public: MbedJSONValue get(std::string url) {
        return get(url, NULL);
    }

    public: MbedJSONValue get(std::string url, HttpOptions* httpOptions) {
        return httpRequest(url, HTTP_GET, httpOptions, "");
    }

    public: MbedJSONValue post(std::string url, std::string body) {
        return post(url, body, NULL);
    }

    public: MbedJSONValue post(std::string url, std::string body, HttpOptions* httpOptions) {
        return httpRequest(url, HTTP_POST, httpOptions, body);
    }

    private: MbedJSONValue httpRequest(std::string url, http_method httpMethod, HttpOptions* httpOptions, std::string body) {
        // TODO maybe use intercetors?
        // TODO log stuff here
        // TODO improve response logging
        
        if (httpOptions && httpOptions->getQueryParams().size() > 0) {
            url = url + "?";
            
            for (int i = 0; i < httpOptions->getQueryParams().size(); i++) {
                std::pair<std::string, std::string> queryParam = httpOptions->getQueryParams().at(i);
                url = url + queryParam.first + "=" + queryParam.second + "&";
            }
        }

        HttpRequest* httpRequest = new HttpRequest(wifiInterface, httpMethod, url.c_str());

        httpOptions = httpOptions ? httpOptions : new HttpOptions();
        httpOptions->addHeader("Content-Type", "application/json");
        
        for (int i = 0; i < httpOptions->getHeaders().size(); i++) {
            std::pair<std::string, std::string> header = httpOptions->getHeaders().at(i);
            httpRequest->set_header(header.first, header.second);
        }
        
        HttpResponse* httpRespone = NULL;

        if (strlen(body.c_str()) > 0) {
            httpRespone = httpRequest->send(body.c_str(), strlen(body.c_str()));
        } else {
            httpRespone = httpRequest->send();
        }

        if (httpRespone) {
            MbedJSONValue responseBodyAsJson;
            parse(responseBodyAsJson, httpRespone->get_body_as_string().c_str());
            delete httpRequest;
            
            return responseBodyAsJson;
        } else {
            ExceptionUtils::throwException("Http Request failed with code ", httpRequest->get_error());

            return NULL;
        }
    }
};