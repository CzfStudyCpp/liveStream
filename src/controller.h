#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "UserServiceInterface.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <memory>

#include "user.grpc.pb.h"

class UserServiceController {
public:
    UserServiceController();
    
    // 处理查询用户请求
    void handle_query_user(web::http::http_request request);

    // 处理发送短信请求
    void handle_send_sms(web::http::http_request request);

    // 处理手机登录请求
    void handle_mobile_login(web::http::http_request request);

    // 处理创建登录 Token 请求
    void handle_create_login_token(web::http::http_request request);

private:
    void initialize_grpc_stub();  // 初始化 gRPC Stub
    std::unique_ptr<user::UserService::Stub> stub_;  // gRPC Stub
};

void RunHTTPServer(std::shared_ptr<UserServiceController> controller);

#endif // CONTROLLER_H
