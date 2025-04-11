#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <memory>
#include <iostream>
#include <thread>  
#include "controller.h"

int main() {
    // 创建 UserServiceController 对象
    std::shared_ptr<UserServiceController> controller = std::make_shared<UserServiceController>();

    // 启动 HTTP 服务器
    std::cout << "Starting HTTP server..." << std::endl;

    // 调用 RunHTTPServer 来启动 HTTP 服务器并保持其运行
    RunHTTPServer(controller);

    return 0;
}