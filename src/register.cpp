#include "ServiceRegistrar.h"
#include <iostream>

int main() {
    // 用户服务信息
    std::string user_service_name = "user-service";
    std::string user_service_id = "user-service-1";
    std::string user_service_address = "192.168.31.128";  // 服务地址
    int user_service_port = 50051;  // 服务端口号

    // HTTP 服务信息
    std::string http_service_name = "http-server";
    std::string http_service_id = "http-server-1";
    std::string http_service_address = "192.168.31.128";  // 服务地址
    int http_service_port = 8080;  // 服务端口号

    // RTMP 服务信息
    std::string rtmp_service_name = "nginx-rtmp-server";
    std::string rtmp_service_id = "nginx-rtmp-server-1";
    std::string rtmp_service_address = "192.168.31.128";  // 服务地址
    int rtmp_service_port = 1935;  // 服务端口号

    // 创建 ServiceRegistrar 对象并注册多个服务
    ServiceRegistrar user_service_registrar(user_service_name, user_service_id, user_service_address, user_service_port);
    ServiceRegistrar http_service_registrar(http_service_name, http_service_id, http_service_address, http_service_port);
    ServiceRegistrar rtmp_service_registrar(rtmp_service_name, rtmp_service_id, rtmp_service_address, rtmp_service_port);

    // 注册服务
    if (user_service_registrar.register_service()) {
        std::cout << "User service registered successfully!" << std::endl;
    } else {
        std::cerr << "User service registration failed!" << std::endl;
    }

    if (http_service_registrar.register_service()) {
        std::cout << "HTTP service registered successfully!" << std::endl;
    } else {
        std::cerr << "HTTP service registration failed!" << std::endl;
    }

    if (rtmp_service_registrar.register_service()) {
        std::cout << "RTMP service registered successfully!" << std::endl;
    } else {
        std::cerr << "RTMP service registration failed!" << std::endl;
    }

    // 注销服务（退出时或其他需要注销时调用）
    if (user_service_registrar.deregister_service()) {
        std::cout << "User service deregistered successfully!" << std::endl;
    } else {
        std::cerr << "User service deregistration failed!" << std::endl;
    }

    if (http_service_registrar.deregister_service()) {
        std::cout << "HTTP service deregistered successfully!" << std::endl;
    } else {
        std::cerr << "HTTP service deregistration failed!" << std::endl;
    }

    if (rtmp_service_registrar.deregister_service()) {
        std::cout << "RTMP service deregistered successfully!" << std::endl;
    } else {
        std::cerr << "RTMP service deregistration failed!" << std::endl;
    }

    return 0;
}
