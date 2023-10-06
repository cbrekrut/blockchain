cmake_minimum_required(VERSION 3.26)
project(blockchain)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(core)
include_directories(ui)

# Найдите библиотеку OpenSSL
find_package(OpenSSL REQUIRED)

add_executable(blockchain
        main.cpp
        README.md
        block.h
        block.cpp)

# Линкуем библиотеки OpenSSL
target_link_libraries(blockchain OpenSSL::Crypto)
