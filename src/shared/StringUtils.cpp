#include <iostream>
#include <string>
#include <vector>
#include "http_request.h"
#include "mbed.h"
#pragma once

class StringUtils {

    public: static bool isEmpty(std::string s) {
        return s.size() > 0;
    }

    public: static std::string toString(bool value) {
        return value ? "true" : "false";
    }
    
    public: static std::string toString(uint8_t value) {
        return std::string((char *)value);
    }

    public: static std::string concat(std::string s1, std::string s2) {
        return s1 + s2;
    }

    public: static std::string concat(std::string s1, std::string s2, std::string s3) {
        return s1 + s2 + s3;
    }

    public: static std::string concat(std::string s1, std::string s2, std::string s3, std::string s4) {
        return s1 + s2 + s3 + s4;
    }

    public: static std::string concat(std::string s1, std::string s2, std::string s3, std::string s4, std::string s5, std::string s6, std::string s7, std::string s8, std::string s9, std::string s10, std::string s11) {
        return s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10 + s11;
    }

/*
    // TODO onvestiogater futher
    public: static std::string yeet(std::string s1, int argsSize, ...) {
        va_list args;


        va_start(args, argsSize);
        string s = ""; 
        for (int i = 0; i < argsSize; i++) {
            s = s + va_arg(args, char*); 
        }
        va_end(args);

        return s;
    }*/

    

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