#include <thread>
#include "controller.h"
#include "grpc_server.h"
#include "user_service_impl.h"
#include "service_interface.h"

int main() {
	
    RunGRPCServer();  // 启动 gRPC 服务
  
    return 0;
}
