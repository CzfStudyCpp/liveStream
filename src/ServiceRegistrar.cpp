#include "ServiceRegistrar.h"
#include <ppconsul/agent.h>
#include <chrono>
#include <iostream>

using namespace ppconsul;

ServiceRegistrar::ServiceRegistrar(const std::string &service_name,
                                   const std::string &service_id,
                                   const std::string &service_address,
                                   int port)
    : service_name_(service_name),
      service_id_(service_id),
      service_address_(service_address),
      port_(port),
      consul_("http://127.0.0.1:8500"), // 指定Consul地址
      agent_(consul_) {}

bool ServiceRegistrar::register_service() {
    try {
        agent_.registerService(
            agent::kw::name = service_name_,
            agent::kw::id = service_id_,
            agent::kw::address = service_address_,
            agent::kw::port = port_,
            agent::kw::check = agent::TtlCheck{std::chrono::seconds(10)}
        );

        std::cout << "Service " << service_name_ << " registered." << std::endl;

        // 启动心跳上报线程
        start_health_check_loop();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to register service: " << e.what() << std::endl;
        return false;
    }
}

bool ServiceRegistrar::deregister_service() {
    try {
        agent_.deregisterService(service_id_);
        std::cout << "Service " << service_name_ << " deregistered." << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to deregister service: " << e.what() << std::endl;
        return false;
    }
}

void ServiceRegistrar::start_health_check_loop() {
    std::thread([this]() {
        while (true) {
            try {
                agent_.pass(service_id_);
                std::this_thread::sleep_for(std::chrono::seconds(5));
            } catch (const std::exception& e) {
                std::cerr << "Health check failed: " << e.what() << std::endl;
            }
        }
    }).detach();
}
