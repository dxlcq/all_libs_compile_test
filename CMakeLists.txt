cmake_minimum_required(VERSION 3.16)
project(AllLibsCompileTest VERSION 1.0.0.0418 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)    # 引入 ExternalProject 模块，可以在构建过程中下载、配置、编译和安装外部项目

# 检测平台 arm64 or amd64
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm|aarch64")
    set(LIB_DIR "lib64")
else()
    set(LIB_DIR "lib")
endif()

# cyclonedds构建
ExternalProject_Add(cyclonedds
    PREFIX ${CMAKE_BINARY_DIR}/cyclonedds
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/cyclonedds-0.10.5
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/cyclonedds/install
)

# cyclonedds-cxx 构建，依赖于 cyclonedds
ExternalProject_Add(cyclonedds-cxx
    DEPENDS cyclonedds
    PREFIX ${CMAKE_BINARY_DIR}/cyclonedds-cxx
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/cyclonedds-cxx-0.10.5
    CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/cyclonedds-cxx/install
        -DCycloneDDS_DIR=${CMAKE_BINARY_DIR}/cyclonedds/install/${LIB_DIR}/cmake/CycloneDDS
)

# cyclonedds-test 构建，依赖于 cyclonedds-cxx
ExternalProject_Add(cyclonedds-ttt
    DEPENDS cyclonedds-cxx
    PREFIX ${CMAKE_BINARY_DIR}/cyclonedds-ttt
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/cyclonedds
    CMAKE_ARGS
        -DCycloneDDS_DIR=${CMAKE_BINARY_DIR}/cyclonedds/install/${LIB_DIR}/cmake/CycloneDDS
        -DCycloneDDS-CXX_DIR=${CMAKE_BINARY_DIR}/cyclonedds-cxx/install/${LIB_DIR}/cmake/CycloneDDS-CXX
        -DCycloneDDS_IDL_COMPILER=${CMAKE_BINARY_DIR}/cyclonedds/install/bin/idlc
    INSTALL_COMMAND ""
)

# taskflow
set(TASKFLOW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/taskflow-3.9.0)
add_subdirectory(taskflow ${CMAKE_BINARY_DIR}/taskflow)