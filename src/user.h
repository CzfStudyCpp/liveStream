#ifndef USER_SERVICE_IMPL_H
#define USER_SERVICE_IMPL_H

#include "user.grpc.pb.h"  // gRPC 自动生成的服务类
#include "service_interface.h"  // 自定义接口类
#include <grpcpp/grpcpp.h>  // gRPC 库

// 实现 UserService 服务并继承 gRPC 的 Service 类
class UserServiceImpl final : public user::UserService::Service, public UserServiceInterface {
public:
    // gRPC 服务方法
    grpc::Status QueryUser(grpc::ServerContext* context, const user::QueryUserRequest* request, user::QueryUserResponse* response) override;
    grpc::Status SendSMS(grpc::ServerContext* context, const user::SendSMSRequest* request, user::WebResponse* response) override;
    grpc::Status MobileLogin(grpc::ServerContext* context, const user::MobileLoginRequest* request, user::MobileLoginResponse* response) override;
    grpc::Status CreateLoginToken(grpc::ServerContext* context, const user::CreateLoginTokenRequest* request, user::CreateLoginTokenResponse* response) override;

    // 实现业务接口方法
    grpc::Status QueryUser(int64_t user_id, user::QueryUserResponse* response) override;
    grpc::Status SendSMS(const std::string& mobile, user::WebResponse* response) override;
    grpc::Status MobileLogin(const std::string& mobile, int code, user::MobileLoginResponse* response) override;
    grpc::Status CreateLoginToken(int64_t user_id, user::CreateLoginTokenResponse* response) override;
};

#endif // USER_SERVICE_IMPL_H
