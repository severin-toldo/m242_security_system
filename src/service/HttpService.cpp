#include <cstdlib>
#include <cstring>
#include <iostream>
#include "mbed.h"
#include "src/shared/PrintUtils.cpp"
#include "src/shared/ExceptionUtils.cpp"
#include "src/shared/StringUtils.cpp"
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
        logRequest(url, httpMethod, httpOptions, body);
        
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
        
        HttpResponse* httpResponse = NULL;

        if (strlen(body.c_str()) > 0) {
            httpResponse = httpRequest->send(body.c_str(), strlen(body.c_str()));
        } else {
            httpResponse = httpRequest->send();
        }

        logResponse(httpResponse);
        delete httpRequest;

        if (httpResponse) {
            MbedJSONValue responseBodyAsJson;
            parse(responseBodyAsJson, httpResponse->get_body_as_string().c_str());
            
            return responseBodyAsJson;
        } else {
            return NULL;
        }
    }

    // TODO request method to string
    private: void logRequest(std::string url, http_method httpMethod, HttpOptions* httpOptions, std::string body) {
        PrintUtils::print("Request:");
        PrintUtils::print("URL: ", url);
        PrintUtils::print("METHOD: ", httpMethod);
        // PrintUtils::print("HEADERS: ", StringUtils::toString(httpOptions->getHeaders()));
        // PrintUtils::print("QUERY PARAMS: ", StringUtils::toString(httpOptions->getQueryParams()));
        PrintUtils::print("REQUEST BODY: ", body);
        PrintUtils::print();
    }

    // TODO status code to string
    private: void logResponse(HttpResponse* httpResponse) {
        if (httpResponse) {
            PrintUtils::print("Response:");
            PrintUtils::print("STATUS CODE: ", httpResponse->get_status_code());
            PrintUtils::print("STATUS MESSAGE: ", httpResponse->get_status_message());
            PrintUtils::print("RESPONSE BODY: ", httpResponse->get_body_as_string());
            PrintUtils::print();
            PrintUtils::print();
        } else  {
            PrintUtils::print("Could not get any response.");
            PrintUtils::print();
        }
    }
};