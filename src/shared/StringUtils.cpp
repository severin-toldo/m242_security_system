#include <string>
#include <vector>
#include "http_request.h"
#include "mbed.h"
#pragma once

class StringUtils {

    public: static std::string concat(std::string s1, std::string s2) {
        return s1 + s2;
    }

    public: static std::string concat(std::string s1, std::string s2, std::string s3) {
        return s1 + s2 + s3;
    }

    public: static std::string concat(std::string s1, std::string s2, std::string s3, std::string s4) {
        return s1 + s2 + s3 + s4;
    }

    public: static bool isEmpty(std::string s) {
        return s.size() > 0;
    }

    public: static std::string toString(bool b) {
        return b ? "true" : "false";
    }

    /*
    public: static std::string toString(std::vector<std::pair<std::string, std::string>> value) {
        std::string s = "[";

        for (int i = 0; i < value.size(); i++) {
            std::pair<std::string, std::string> p = value.at(i);

            s = s + "{" + p.first + "=" + p.second + "}";

            if (i != (value.size() - 1)) {
                s = s + ", ";
            }
        }

        return s + "]";
    };
    */
};