#include "user_service_impl.h"

// gRPC 服务方法
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

// 业务接口方法的实现
grpc::Status UserServiceImpl::QueryUser(int64_t user_id, user::QueryUserResponse* response) {
    // 模拟业务逻辑，返回用户数据
    user::UserDTO user;
    user.set_user_id(user_id);
    user.set_nick_name("John Doe");
    user.set_true_name("John");
    user.set_avatar("http://example.com/avatar.jpg");
    user.set_sex(1);  // 男
    user.set_create_time("2022-01-01 12:00:00");
    user.set_update_time("2022-01-01 12:00:00");

    response->mutable_user()->CopyFrom(user);
    return grpc::Status::OK;
}

grpc::Status UserServiceImpl::SendSMS(const std::string& mobile, user::WebResponse* response) {
    // 模拟发送短信验证码
    response->set_code(200);
    response->set_message("SUCCESS");
    return grpc::Status::OK;
}

grpc::Status UserServiceImpl::MobileLogin(const std::string& mobile, int code, user::MobileLoginResponse* response) {
    // 模拟手机登录
    response->set_login_success(true);
    response->set_token("token123");
    response->set_message("Login successful");
    return grpc::Status::OK;
}

grpc::Status UserServiceImpl::CreateLoginToken(int64_t user_id, user::CreateLoginTokenResponse* response) {
    // 模拟生成 Token
    response->set_token("token123");
    return grpc::Status::OK;
}
