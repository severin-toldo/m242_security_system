#include <cstdlib>
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
        if (httpOptions && httpOptions->getQueryParams().size() > 0) {
            url = url + "?";
            
            for (int i = 0; i < httpOptions->getQueryParams().size(); i++) {
                std::pair<std::string, std::string> queryParam = httpOptions->getQueryParams().at(i);
                url = url + queryParam.first + "=" + queryParam.second + "&";
            }
        }

        PrintUtils::print("url: ", url);
        
        HttpRequest* httpRequest = new HttpRequest(wifiInterface, HTTP_GET, url.c_str());

        if (httpOptions) {
            for (int i = 0; i < httpOptions->getHeaders().size(); i++) {
                std::pair<std::string, std::string> header = httpOptions->getHeaders().at(i);
                httpRequest->set_header(header.first, header.second);
            }
        }
        
        HttpResponse* httpRespone = httpRequest->send();

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




    /*
    public: void tmp2() {
        HttpRequest* get_req = new HttpRequest( network, HTTP_POST, message );

        HttpResponse* get_res = get_req->send();
        if (!get_res)
        {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return 1;
        }
        delete get_req;
    }
    */







};