#ifndef SERVICE_INTERFACE_H
#define SERVICE_INTERFACE_H

#include "user.grpc.pb.h"
#include "user.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>

class UserServiceInterface {
public:
   virtual grpc::Status QueryUser(int64_t user_id, user::QueryUserResponse* response) = 0;
    virtual grpc::Status SendSMS(const std::string& mobile, user::WebResponse* response) = 0;
    virtual grpc::Status MobileLogin(const std::string& mobile, int code, user::MobileLoginResponse* response) = 0;
    virtual grpc::Status CreateLoginToken(int64_t user_id, user::CreateLoginTokenResponse* response) = 0;
    virtual grpc::Status ValidateToken(const std::string& token, user::ValidateTokenResponse* response) = 0;
    virtual ~UserServiceInterface() = default;
};

#endif // SERVICE_INTERFACE_H
