#include <string>
#include <vector>
#include "src/shared/PrintUtils.cpp"
#pragma once


class HttpOptions {
    private: std::vector<std::pair<std::string, std::string>> headers;
    private: std::vector<std::pair<std::string, std::string>> queryParams;


    public: std::vector<std::pair<std::string, std::string>> getHeaders() {
        return headers;
    }

    public: void setHeaders(std::vector<std::pair<std::string, std::string>> headers) {
        this->headers = headers;
    }

    public: void addHeader(std::string key, std::string value) {
        std::pair<std::string, std::string> header;
        header.first = key;
        header.second = value;

        headers.insert(headers.begin(), header);
    }

    public: std::vector<std::pair<std::string, std::string>> getQueryParams() {
        return queryParams;
    }

    public: void setQueryParams(std::vector<std::pair<std::string, std::string>> queryParams) {
        this->queryParams = queryParams;
    }

    public: void addQueryParam(std::string key, std::string value) {
        std::pair<std::string, std::string> queryParam;
        queryParam.first = key;
        queryParam.second = value;

        queryParams.insert(queryParams.begin(), queryParam);
    }
};