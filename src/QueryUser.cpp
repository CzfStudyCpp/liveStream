#include "user.grpc.pb.h"
#include "user.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>

std::unique_ptr<user::UserService::Stub> stub_;


void QueryUser(int64_t user_id) {
    user::QueryUserRequest request;
    request.set_user_id(user_id);

    user::QueryUserResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->QueryUser(&context, request, &response);

    if (status.ok()) {
        std::cout << "User Info: " << response.user().nick_name() << std::endl;
    } else {
        std::cout << "Error: " << status.error_message() << std::endl;
    }
}

int main() {
    std::string server_address("localhost:50051");  // Make sure the address is correct
    stub_ = user::UserService::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    int64_t user_id = 123;  // Example user ID
    std::cout << "Requesting user info for user ID: " << user_id << std::endl;
    QueryUser(user_id);

    return 0;
}


