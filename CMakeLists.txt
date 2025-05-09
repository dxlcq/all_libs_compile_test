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

option(BUILD_tttt_cyclonedds "Build tttt-cyclonedds" OFF)
option(BUILD_tttt_taskflow "Build tttt-taskflow" OFF)
option(BUILD_tttt_subprocess "Build tttt-subprocess" OFF)
option(BUILD_tttt_rocksdb "Build tttt-rocksdb" OFF)
option(BUILD_tttt_ssdb "Build tttt-ssdb" ON)

# tttt-cyclonedds，依赖于 cyclonedds-cxx
if(BUILD_tttt_cyclonedds)
    # cyclonedds 构建
    ExternalProject_Add(cyclonedds
        PREFIX ${CMAKE_BINARY_DIR}/cyclonedds
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/cyclonedds
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/cyclonedds/install
    )

    # cyclonedds-cxx 构建，依赖于 cyclonedds
    ExternalProject_Add(cyclonedds-cxx
        DEPENDS cyclonedds
        PREFIX ${CMAKE_BINARY_DIR}/cyclonedds-cxx
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/cyclonedds-cxx
        CMAKE_ARGS 
            -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/cyclonedds-cxx/install
            -DCycloneDDS_DIR=${CMAKE_BINARY_DIR}/cyclonedds/install/${LIB_DIR}/cmake/CycloneDDS
    )
    
    # tttt-cyclonedds 构建，依赖于 cyclonedds-cxx
    ExternalProject_Add(tttt-cyclonedds
        DEPENDS cyclonedds-cxx
        PREFIX ${CMAKE_BINARY_DIR}/tttt-cyclonedds
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/tttt-cyclonedds
        CMAKE_ARGS
            -DCycloneDDS_DIR=${CMAKE_BINARY_DIR}/cyclonedds/install/${LIB_DIR}/cmake/CycloneDDS
            -DCycloneDDS-CXX_DIR=${CMAKE_BINARY_DIR}/cyclonedds-cxx/install/${LIB_DIR}/cmake/CycloneDDS-CXX
        INSTALL_COMMAND ""
    )
endif()

# tttt-taskflow
if(BUILD_tttt_taskflow)
    set(TASKFLOW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/taskflow)

    add_subdirectory(tttt-taskflow ${CMAKE_BINARY_DIR}/tttt-taskflow)
endif()

# tttt-subprocess
if(BUILD_tttt_subprocess)
    add_subdirectory(libs/subprocess ${CMAKE_BINARY_DIR}/subprocess)

    add_subdirectory(tttt-subprocess ${CMAKE_BINARY_DIR}/tttt-subprocess)
endif()

# tttt-rocksdb
if(BUILD_tttt_subprocess)
    # rocksdb 构建
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)           # 设置构建类型为 Release
    set(WITH_GFLAGS OFF CACHE BOOL "build with gflags" FORCE)               # 关闭 gflags 依赖
    set(PORTABLE ON CACHE BOOL "build a portable binary" FORCE)             # 更好的兼容性
    set(ROCKSDB_BUILD_SHARED OFF CACHE BOOL "build shared library" FORCE)   # 仅构建静态库
    set(WITH_TESTS OFF CACHE BOOL "build with tests" FORCE)                 # 不构建测试
    set(WITH_TOOLS OFF CACHE BOOL "build with tools" FORCE)                 # 不构建工具
    add_subdirectory(libs/rocksdb ${CMAKE_BINARY_DIR}/rocksdb)

    add_subdirectory(tttt-rocksdb ${CMAKE_BINARY_DIR}/tttt-rocksdb)
endif()

# tttt-ssdb
if(BUILD_tttt_ssdb)

    # ssdb 构建
    add_custom_target(ssdb ALL
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/ssdb
        COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/* ${CMAKE_BINARY_DIR}/ssdb/
        COMMAND cd ${CMAKE_BINARY_DIR}/ssdb && make
    )

    add_subdirectory(tttt-ssdb ${CMAKE_BINARY_DIR}/tttt-ssdb)
endif()