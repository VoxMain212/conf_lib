cmake_minimum_required(VERSION 3.10)

project(conf_lib VERSION 0.1 LANGUAGES CXX)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_executable(conf_lib example\\main.cpp)
