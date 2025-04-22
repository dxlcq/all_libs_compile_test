cmake_minimum_required(VERSION 3.16)
project(tttt-ssdb VERSION 1.0.0.0422 LANGUAGES CXX)

add_executable(tttt-ssdb
    ssdb.cpp
)

target_link_libraries(tttt-ssdb PRIVATE
    libssdb-client.a
)