#include <iostream>

#include "log.hpp"

void log_info(std::string str) {
    std::cout << "\e[4m\e[3m\e[1;34m[Info]\e[0m - " << str << std::endl;
}
