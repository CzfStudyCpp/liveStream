#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include "user.grpc.pb.h"
#include "user.pb.h"
#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>

class UserServiceImpl final : public user::UserService::Service {
public:
    grpc::Status QueryUser(grpc::ServerContext* context, const user::QueryUserRequest* request, user::QueryUserResponse* response) override {
        int64_t user_id = request->user_id();

        // 假设这里是查询用户数据的模拟操作
        user::UserDTO user;
        user.set_user_id(user_id);
        user.set_nick_name("John Doe");
        user.set_true_name("John");
        user.set_avatar("http://example.com/avatar.jpg");
        user.set_sex(1); // 男
        user.set_create_time("2022-01-01 12:00:00");
        user.set_update_time("2022-01-01 12:00:00");

        response->mutable_user()->CopyFrom(user);
        return grpc::Status::OK;
    }

    grpc::Status SendSMS(grpc::ServerContext* context, const user::SendSMSRequest* request, user::WebResponse* response) override {
        std::string mobile = request->mobile();
        std::cout << "Sending SMS to: " << mobile << std::endl;

        // 模拟发送验证码
        response->set_code(200);
        response->set_message("SUCCESS");
        return grpc::Status::OK;
    }

    grpc::Status MobileLogin(grpc::ServerContext* context, const user::MobileLoginRequest* request, user::MobileLoginResponse* response) override {
        std::string mobile = request->mobile();
        int code = request->code();

        // 模拟校验验证码
        std::cout << "Checking code " << code << " for mobile " << mobile << std::endl;

        // 假设登录成功
        response->set_login_success(true);
        response->set_token("token123");
        response->set_message("Login successful");

        return grpc::Status::OK;
    }

    grpc::Status CreateLoginToken(grpc::ServerContext* context, const user::CreateLoginTokenRequest* request, user::CreateLoginTokenResponse* response) override {
        std::string token = "token123";  // 模拟生成的 Token
        std::cout << "Creating token for user " << request->user_id() << std::endl;

        // 这里可以存储 token 和 user_id 映射
        response->set_token(token);
        return grpc::Status::OK;
    }
};

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

// 处理 REST API 请求
void handle_query_user(web::http::http_request request) {
    web::http::http_response response;
    response.set_status_code(web::http::status_codes::OK);

    // 请求处理逻辑
    std::string user_id_str = request.query_string();
    int64_t user_id = std::stoi(user_id_str);
    
    // 调用 gRPC 服务查询用户信息
    // 这里简化处理，直接返回静态的用户数据
    web::json::value user_data;
    user_data[U("user_id")] = web::json::value::number(user_id);
    user_data[U("nick_name")] = web::json::value::string("John Doe");
    user_data[U("true_name")] = web::json::value::string("John");

    response.set_body(user_data);
    request.reply(response);
}

int main() {
    // 启动 gRPC 服务
    std::thread grpc_server_thread(RunServer);

    // 使用 cpprestsdk 创建 REST API 服务
    web::http::experimental::listener::http_listener listener("http://localhost:8080");
    listener.support(web::http::methods::POST, handle_query_user);
    listener
        .open()
        .then([]() { std::cout << "Listening on http://localhost:8080..." << std::endl; })
        .wait();

    grpc_server_thread.join();  // 等待 gRPC 服务线程结束
    return 0;
}

