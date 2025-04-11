
#include "UserService.h"
#include<iostream>
#include "user.grpc.pb.h"  // 引入 gRPC 生成的文件
#include <grpcpp/grpcpp.h>

// 启动 gRPC 服务
void RunServer() {
    std::string server_address("0.0.0.0:50051");
    UserServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}