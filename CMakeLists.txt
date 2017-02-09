cmake_minimum_required(VERSION 3.6)
project(Cryptography)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TransCipher.cpp routecipher.cpp decr_routeCipher.cpp)
add_executable(Cryptography ${SOURCE_FILES})