#include "user.grpc.pb.h"
#include "user.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <unordered_map>
#include <string>

// 模拟 Token 存储
std::unordered_map<std::string, int64_t> token_store;

class UserServiceImpl final : public user::UserService::Service {
public:
    // 查询用户信息
   grpc::Status QueryUser(grpc::ServerContext* context, const user::QueryUserRequest* request, user::QueryUserResponse* response) override {
    std::cout << "Received request to query user with ID: " << request->user_id() << std::endl;

    int64_t user_id = request->user_id();
    
    // 模拟查询到的用户信息
    user::UserDTO user;
    user.set_user_id(user_id);
    user.set_nick_name("John Doe");
    user.set_true_name("John");
    user.set_avatar("http://example.com/avatar.jpg");
    user.set_sex(1); // 1 = Male
    user.set_create_time("2022-01-01 12:00:00");
    user.set_update_time("2022-01-01 12:00:00");
    
    response->mutable_user()->CopyFrom(user);
    
    std::cout << "Returning user info for ID: " << user_id << std::endl;
    
    return grpc::Status::OK;
}


    // 发送短信验证码
    grpc::Status SendSMS(grpc::ServerContext* context, const user::SendSMSRequest* request, user::WebResponse* response) override {
        std::string mobile = request->mobile();
        std::cout << "Sending SMS to: " << mobile << std::endl;
        
        // 模拟发送验证码
        response->set_code(200);
        response->set_message("SUCCESS");
        
        return grpc::Status::OK;
    }

    // 手机验证码登录
    grpc::Status MobileLogin(grpc::ServerContext* context, const user::MobileLoginRequest* request, user::MobileLoginResponse* response) override {
        std::string mobile = request->mobile();
        int32_t code = request->code();
        
        // 模拟校验验证码
        std::cout << "Checking code " << code << " for mobile " << mobile << std::endl;
        
        // 假设登录成功
        response->set_login_success(true);
        response->set_token("token123");
        response->set_message("Login successful");

        return grpc::Status::OK;
    }

    // 验证 Token
    grpc::Status ValidateToken(grpc::ServerContext* context, const user::ValidateTokenRequest* request, user::ValidateTokenResponse* response) override {
        std::string token = request->token();

        // 检查 token 是否有效
        if (token_store.find(token) != token_store.end()) {
            response->set_is_valid(true);
            response->set_user_id(std::to_string(token_store[token]));
            response->set_message("Token is valid");
        } else {
            response->set_is_valid(false);
            response->set_message("Invalid token");
        }

        return grpc::Status::OK;
    }

    // 创建登录 Token
    grpc::Status CreateLoginToken(grpc::ServerContext* context, const user::CreateLoginTokenRequest* request, user::CreateLoginTokenResponse* response) override {
        std::string token = "token123";  // 模拟生成的 Token
        std::cout << "Creating token for user " << request->user_id() << std::endl;
        
        // 存储 token 和 user_id 映射
        token_store[token] = request->user_id();
        
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

int main() {
    RunServer();
    return 0;
}

