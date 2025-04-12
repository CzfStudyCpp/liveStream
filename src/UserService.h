#ifndef USER_SERVICE_IMPL_H
#define USER_SERVICE_IMPL_H

#include "UserServiceInterface.h"
#include "user.grpc.pb.h"  // 引入 gRPC 生成的文件
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <unordered_map>
#include <string>


class UserServiceImpl final : public user::UserService::Service,public UserServiceInterface {
	
public:
    // 查询用户信息
    grpc::Status QueryUser(grpc::ServerContext* context, const user::QueryUserRequest* request, user::QueryUserResponse* response) override;

    // 发送短信验证码
    grpc::Status SendSMS(grpc::ServerContext* context, const user::SendSMSRequest* request, user::WebResponse* response) override;

    // 手机验证码登录
    grpc::Status MobileLogin(grpc::ServerContext* context, const user::MobileLoginRequest* request, user::MobileLoginResponse* response) override;

    // 验证 Token
    grpc::Status ValidateToken(grpc::ServerContext* context, const user::ValidateTokenRequest* request, user::ValidateTokenResponse* response) override;

    // 创建登录 Token
    grpc::Status CreateLoginToken(grpc::ServerContext* context, const user::CreateLoginTokenRequest* request, user::CreateLoginTokenResponse* response) override;
	
	
	
	
    // 接口方法实现
    grpc::Status QueryUser(int64_t user_id, user::QueryUserResponse* response) override;
    grpc::Status SendSMS(const std::string& mobile, user::WebResponse* response) override;
    grpc::Status MobileLogin(const std::string& mobile, int code, user::MobileLoginResponse* response) override;
    grpc::Status CreateLoginToken(int64_t user_id, user::CreateLoginTokenResponse* response) override;
    grpc::Status ValidateToken(const std::string& token, user::ValidateTokenResponse* response) override;

private:
    // 模拟 Token 存储
    std::unordered_map<std::string, int64_t> token_store;
};

#endif // USER_SERVICE_IMPL_H
