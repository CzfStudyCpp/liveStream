#ifndef SERVICE_REGISTRAR_H
#define SERVICE_REGISTRAR_H

#include <string>
#include <curl/curl.h>

class ServiceRegistrar {
public:
    // 构造函数：传入服务名称、服务实例 ID、服务地址、端口号
    ServiceRegistrar(const std::string &service_name, const std::string &service_id, 
                     const std::string &service_address, int port = 8080);

    // 注册服务
    bool register_service();
    
    // 注销服务
    bool deregister_service();
    
private:
    std::string service_name_;
    std::string service_id_;
    std::string service_address_;
    int port_;
    std::string consul_url_ = "http://localhost:8500/v1/agent/service/register";
    std::string deregister_url_ = "http://localhost:8500/v1/agent/service/deregister/";

    bool send_http_request(const std::string &url, const std::string &data);
};

#endif
