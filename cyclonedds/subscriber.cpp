#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "HelloWorldData.hpp"  // 需要使用的消息类型
#include "dds/dds.hpp"         // Cyclone DDS C++ API

using namespace org::eclipse::cyclonedds;

int main() {
    try {
        std::cout << "=== [Subscriber] Create reader." << std::endl;

        dds::domain::DomainParticipant participant(domain::default_id());               // domain participant，domain 的入口
        dds::topic::Topic<HelloWorldData::Msg> topic(participant, "HelloWorldData_Msg");// 向 domain participant 注册 topic
        dds::sub::Subscriber subscriber(participant);                                   // subscriber 
        dds::sub::DataReader<HelloWorldData::Msg> reader(subscriber, topic);            // subscriber 的 reader，绑定一个 topic

        std::cout << "=== [Subscriber] Wait for message." << std::endl;
        for (bool poll = true; poll;) {
            dds::sub::LoanedSamples<HelloWorldData::Msg> samples;                       // 数据容器，用于从 reader 中读取数据
            samples = reader.take();                                                    // 从 reader 中读取数据

            if (samples.length() > 0) {                                                 // 如果读取到数据
                for (auto sample_iter : samples) {                                      // 遍历读取到的数据
                    const HelloWorldData::Msg& msg = sample_iter->data();               // 获取数据
                    const dds::sub::SampleInfo& info = sample_iter->info();             // 获取数据的状态信息

                    if (info.valid()) {                                                 // 如果数据有效
                        std::cout << "=== [Subscriber] Message received:" << std::endl;
                        std::cout << "    userID  : " << msg.userID() << std::endl;
                        std::cout << "    Message : \"" << msg.message() << "\"" << std::endl;
                        poll = false;                                                   // 只读取一次
                    }
                }
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));             // 如果没有读取到数据，等待 20 毫秒再尝试读取
            }
        }
    } catch (const dds::core::Exception& e) {
        std::cerr << "=== [Subscriber] DDS exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "=== [Subscriber] C++ exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "=== [Subscriber] Done." << std::endl;

    return EXIT_SUCCESS;
}