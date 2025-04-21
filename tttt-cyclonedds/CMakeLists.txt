find_package(CycloneDDS-CXX REQUIRED)
idlcxx_generate(TARGET helloworlddata FILES HelloWorldData.idl WARNINGS no-implicit-extensibility)

# 生成可执行文件
add_executable(ddscxxHelloworldPublisher publisher.cpp)
add_executable(ddscxxHelloworldSubscriber subscriber.cpp)

# 将两个可执行文件链接到 idl 数据类型库和 ddscxx
target_link_libraries(ddscxxHelloworldPublisher CycloneDDS-CXX::ddscxx helloworlddata)
target_link_libraries(ddscxxHelloworldSubscriber CycloneDDS-CXX::ddscxx helloworlddata)