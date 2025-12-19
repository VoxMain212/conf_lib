#include "../include/conf_lib.hpp"
#include <iostream>
#include <string>


int main()
{
    conf_lib::CONFIG conf;
    conf.open("test.ini");
    std::cout << std::get<std::string>(conf["label2"]["asldkalskd"]);

    return 0;
}