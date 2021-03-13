#include <cstdlib>
#include <iostream>
#include "src/shared/PrintUtils.cpp"
#pragma once

class ExceptionUtils {

    public: static void throwException(std::string message, int param) {
        throwException(message, std::to_string(param));
    }

    public: static void throwException(std::string message, long param) {
        throwException(message, std::to_string(param));
    }

    public: static void throwException(std::string message, float param) {
        throwException(message, std::to_string(param));
    }

    public: static void throwException(std::string message, double param) {
        throwException(message, std::to_string(param));
    }

    public: static void throwException(std::string message) {
        throwException(message, "");
    }

    public: static void throwException(std::string message, std::string param) {
        PrintUtils::print("EXCEPTION: " + message, param);
        exit(-1);
    }

};