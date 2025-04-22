cmake_minimum_required(VERSION 3.16)
project(tttt-rocksdb VERSION 1.0.0.0421 LANGUAGES CXX)

# 生成可执行文件
add_executable(tttt-rocksdb rocksdb.cpp)

# 链接动态库
target_link_libraries(tttt-rocksdb PRIVATE
    rocksdb
)