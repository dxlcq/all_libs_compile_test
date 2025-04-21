cmake_minimum_required(VERSION 3.16)
project(tttt-subprocess VERSION 1.0.0.0421 LANGUAGES CXX)

add_executable(tttt-subprocess
    subprocess.cpp
)

target_include_directories(tttt-subprocess PRIVATE
    ${SUBPROCESS_INCLUDE_DIR}
)

target_link_libraries(tttt-subprocess PRIVATE
    subprocess
)