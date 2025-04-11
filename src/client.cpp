#include <grpcpp/grpcpp.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>
#include "user.grpc.pb.h"  // 引入 gRPC 自动生成的代码

// 发送请求获取用户信息
void query_user(const std::string& server_address, int64_t user_id) {
    // 创建与 gRPC 服务器的连接
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    std::unique_ptr<user::UserService::Stub> stub_ = user::UserService::NewStub(channel);

    user::QueryUserRequest request;
    user::QueryUserResponse response;
    grpc::ClientContext context;

    request.set_user_id(user_id);
    
    grpc::Status status = stub_->QueryUser(&context, request, &response);

    if (status.ok()) {
        std::cout << "User Info: " << std::endl;
        std::cout << "User ID: " << response.user().user_id() << std::endl;
        std::cout << "Nick Name: " << response.user().nick_name() << std::endl;
        std::cout << "True Name: " << response.user().true_name() << std::endl;
        std::cout << "Avatar: " << response.user().avatar() << std::endl;
    } else {
        std::cout << "Failed to query user: " << status.error_message() << std::endl;
    }
}

// 发送请求创建登录 Token
void create_login_token(const std::string& server_address, int64_t user_id) {
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    std::unique_ptr<user::UserService::Stub> stub_ = user::UserService::NewStub(channel);

    user::CreateLoginTokenRequest request;
    user::CreateLoginTokenResponse response;
    grpc::ClientContext context;

    request.set_user_id(user_id);
    
    grpc::Status status = stub_->CreateLoginToken(&context, request, &response);

    if (status.ok()) {
        std::cout << "Login Token: " << response.token() << std::endl;
    } else {
        std::cout << "Failed to create login token: " << status.error_message() << std::endl;
    }
}

// HTTP 客户端请求：查询用户
void query_user_http(const std::string& server_url, int64_t user_id) {
    web::http::client::http_client client(server_url);
    web::http::http_request request(web::http::methods::POST);

    // 构造 JSON 请求体
    web::json::value request_body;
    request_body[U("user_id")] = web::json::value::number(user_id);
    request.set_body(request_body);

    client.request(request).then([](web::http::http_response response) {
        if (response.status_code() == web::http::status_codes::OK) {
            // 处理响应
            web::json::value json_response = response.extract_json().get();
            std::cout << "User Info from HTTP Server: " << std::endl; // 修改为 std::cout
            std::cout << "User ID: " << json_response[U("user_id")].as_integer() << std::endl;
            std::cout << "Nick Name: " << json_response[U("nick_name")].as_string() << std::endl;
        } else {
            std::cout << "Failed to query user HTTP: " << response.status_code() << std::endl;
        }
    }).wait();
}

int main() {
    std::string grpc_server_address = "localhost:50051";
    std::string http_server_address = "http://localhost:8080/user/queryUser";

    // 示例：使用 gRPC 查询用户
    query_user(grpc_server_address, 1);

    // 示例：使用 HTTP 查询用户
    query_user_http(http_server_address, 1);

    // 示例：使用 gRPC 创建登录 Token
    create_login_token(grpc_server_address, 1);

    return 0;
}
