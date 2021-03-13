#include <iostream>
#pragma once

class PrintUtils {

    public: static void print(int param) {
        print(std::to_string(param));
    }

    public: static void print(long param) {
        print(std::to_string(param));
    }

    public: static void print(float param) {
        print(std::to_string(param));
    }

    public: static void print(double param) {
        print(std::to_string(param));
    }
   
    public: static void print(std::string message, int param) {
        print(message, std::to_string(param));
    }

    public: static void print(std::string message, long param) {
        print(message, std::to_string(param));
    }

    public: static void print(std::string message, float param) {
        print(message, std::to_string(param));
    }

    public: static void print(std::string message, double param) {
        print(message, std::to_string(param));
    }

    public: static void print() {
        print("", "");
    }

    public: static void print(std::string param) {
        print("", param);
    }

    public: static void print(std::string message, std::string param) {
        std::cout << message << param << "\n";
    }

};