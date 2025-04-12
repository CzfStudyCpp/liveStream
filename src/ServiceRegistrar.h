#ifndef SERVICE_REGISTRAR_H
#define SERVICE_REGISTRAR_H

#include <string>
#include <ppconsul/consul.h>
#include <ppconsul/agent.h>
#include <thread>

class ServiceRegistrar {
public:
    ServiceRegistrar(const std::string &service_name, const std::string &service_id,
                     const std::string &service_address, int port);

    bool register_service();
    bool deregister_service();

private:
    void start_health_check_loop();

    std::string service_name_;
    std::string service_id_;
    std::string service_address_;
    int port_;
    ppconsul::Consul consul_;
    ppconsul::agent::Agent agent_;
};

#endif
