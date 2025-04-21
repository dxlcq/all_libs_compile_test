cmake_minimum_required(VERSION 3.16)
project(tttt-taskflow VERSION 1.0.0.0421 LANGUAGES CXX)

add_executable(taskflow
    taskflow.cpp
)

target_include_directories(taskflow PRIVATE
    ${TASKFLOW_INCLUDE_DIR}
)

target_link_libraries(taskflow PRIVATE
    pthread
)