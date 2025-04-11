#include "UserService.h"
#include <iostream>
// 查询用户信息
grpc::Status UserServiceImpl::QueryUser(int64_t user_id, user::QueryUserResponse* response) {
    std::cout << "Querying user with ID: " << user_id << std::endl;

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
    
    return grpc::Status::OK;
}

// 发送短信验证码
grpc::Status UserServiceImpl::SendSMS(const std::string& mobile, user::WebResponse* response) {
    std::cout << "Sending SMS to: " << mobile << std::endl;
    
    // 模拟发送验证码
    response->set_code(200);
    response->set_message("SUCCESS");
    
    return grpc::Status::OK;
}

// 手机验证码登录
grpc::Status UserServiceImpl::MobileLogin(const std::string& mobile, int code, user::MobileLoginResponse* response) {
    std::cout << "Checking code " << code << " for mobile " << mobile << std::endl;
    
    // 假设登录成功
    response->set_login_success(true);
    response->set_token("token123");
    response->set_message("Login successful");

    return grpc::Status::OK;
}

// 验证 Token
grpc::Status UserServiceImpl::ValidateToken(const std::string& token, user::ValidateTokenResponse* response) {
    std::cout << "Validating token: " << token << std::endl;

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
grpc::Status UserServiceImpl::CreateLoginToken(int64_t user_id, user::CreateLoginTokenResponse* response) {
    std::cout << "Creating token for user " << user_id << std::endl;

    // 模拟生成的 Token
    std::string token = "token123"; 
    
    // 存储 token 和 user_id 映射
    token_store[token] = user_id;
    
    response->set_token(token);
    
    return grpc::Status::OK;
}

// gRPC 方法实现，只调用接口方法
grpc::Status UserServiceImpl::QueryUser(grpc::ServerContext* context, const user::QueryUserRequest* request, user::QueryUserResponse* response) {
    return QueryUser(request->user_id(), response);
}

grpc::Status UserServiceImpl::SendSMS(grpc::ServerContext* context, const user::SendSMSRequest* request, user::WebResponse* response) {
    return SendSMS(request->mobile(), response);
}

grpc::Status UserServiceImpl::MobileLogin(grpc::ServerContext* context, const user::MobileLoginRequest* request, user::MobileLoginResponse* response) {
    return MobileLogin(request->mobile(), request->code(), response);
}

grpc::Status UserServiceImpl::CreateLoginToken(grpc::ServerContext* context, const user::CreateLoginTokenRequest* request, user::CreateLoginTokenResponse* response) {
    return CreateLoginToken(request->user_id(), response);
}

grpc::Status UserServiceImpl::ValidateToken(grpc::ServerContext* context, const user::ValidateTokenRequest* request, user::ValidateTokenResponse* response) {
    return ValidateToken(request->token(), response);
}