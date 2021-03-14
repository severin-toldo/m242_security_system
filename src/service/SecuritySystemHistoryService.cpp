#include "src/service/HttpService.cpp"
#include "src/model/SecuritySystemHistoryCreateRequest.cpp"
#include "src/model/HttpOptions.cpp"
#include "src/shared/Urls.cpp"
#include "src/shared/PrintUtils.cpp"
#include <string>
#pragma once

class SecuritySystemHistoryService {

    private: HttpService* httpService;


    public: SecuritySystemHistoryService(HttpService* httpService) {
        this->httpService = httpService;
    }

    public: bool addHistory(std::string securitySystemAuthToken, int securitySystemId, SecuritySystemHistoryCreateRequest sshcr) {
        HttpOptions* options = new HttpOptions();
        options->addHeader("auth_token", securitySystemAuthToken);

        MbedJSONValue body;
        body["datetime"] = sshcr.getDatetime();
        body["type"] = sshcr.getType();
        body["userRfidUUID"] = sshcr.getUserRfidUUID();

        MbedJSONValue response = httpService->post(Urls::addSecuritySystemHistoryUrl(securitySystemId), body.serialize(), options);
        
        return response.get<bool>();
    }
};