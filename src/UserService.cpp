#include "UserService.h"
#include "dto.h"

#include <iostream>
#include "user.h"  // 包含User类头文件

// 查询用户信息
grpc::Status UserServiceImpl::QueryUser(int64_t user_id, user::QueryUserResponse* response) {
    std::cout << "Querying user with ID: " << user_id << std::endl;

    userInfo user_info;
    User user_service;
    if (user_service.GetUserInfo(user_id, user_info)) {
        // 将获取到的用户信息填充到 gRPC Response 中
        user::UserDTO user;
        user.set_user_id(user_info.user_id);
        user.set_nick_name(user_info.nick_name);
        user.set_true_name(user_info.true_name);
        user.set_avatar(user_info.avatar);
        user.set_sex(user_info.sex);
        user.set_create_time(user_info.create_time);
        user.set_update_time(user_info.update_time);

        response->mutable_user()->CopyFrom(user);
        return grpc::Status::OK;
    } else {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "User not found");
    }
}

// 发送短信验证码
grpc::Status UserServiceImpl::SendSMS(const std::string& mobile, user::WebResponse* response) {
   std::cout << "Sending SMS to: " << mobile << std::endl;

    int code;
    User user_service;
    if (user_service.GenerateVerificationCode(mobile, code)) {
        response->set_code(code);
        response->set_message("SUCCESS");
        return grpc::Status::OK;
    } else {
        return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to generate verification code");
    }
}

// 手机验证码登录
grpc::Status UserServiceImpl::MobileLogin(const std::string& mobile, int code, user::MobileLoginResponse* response) {
     std::cout << "Checking code " << code << " for mobile " << mobile << std::endl;

    bool success;
    std::string token;
    User user_service;
    if (user_service.VerifyCodeLogin(mobile, code, success, token)) {
        if (success) {
            response->set_login_success(true);
            response->set_token(token);
            response->set_message("Login successful");
            return grpc::Status::OK;
        } else {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid verification code");
        }
    } else {
        return grpc::Status(grpc::StatusCode::INTERNAL, "Error during verification");
    }
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

    std::string token;
    User user_service;
    if (user_service.CreateLoginToken(user_id, token)) {
        response->set_token(token);
        return grpc::Status::OK;
    } else {
        return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to create token");
    }
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