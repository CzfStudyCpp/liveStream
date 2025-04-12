#include "controller.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>
#include <thread>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

UserServiceController::UserServiceController() {
    initialize_grpc_stub();  // 初始化 gRPC Stub
}

// 初始化 gRPC Stub
void UserServiceController::initialize_grpc_stub() {
    std::string server_address("localhost:50051");
    std::cout << "初始化grpc stub\n";
    std::cout << "通道初始化++++++++\n\n";
    auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    std::cout << "完成通道初始化++++++++\n\n";
    stub_ = user::UserService::NewStub(channel);
    std::cout << "完成初始化grpc stub\n\n";
}

// 处理查询用户请求
void UserServiceController::handle_query_user(http_request request) {
    web::http::http_response response;
    try {
        // 提取请求中的 JSON 数据
        web::json::value request_body = request.extract_json().get();
        int64_t user_id = request_body[U("user_id")].as_integer();

        // 调用 gRPC 服务查询用户信息
        user::QueryUserRequest query_request;
        query_request.set_user_id(user_id);
        user::QueryUserResponse query_response;
        grpc::ClientContext context;
        grpc::Status status = stub_->QueryUser(&context, query_request, &query_response);

        // 根据 gRPC 的调用结果返回响应
        if (status.ok()) {
            response.set_status_code(web::http::status_codes::OK);
            web::json::value user_data;
            user_data[U("user_id")] = web::json::value::number(query_response.user().user_id());
            user_data[U("nick_name")] = web::json::value::string(query_response.user().nick_name());
            response.set_body(user_data);
        } else {
            response.set_status_code(web::http::status_codes::BadRequest);
            response.set_body("Error retrieving user information.");
        }
    } catch (const std::exception& e) {
        response.set_status_code(web::http::status_codes::BadRequest);
        response.set_body("Invalid request format.");
    }
    request.reply(response);
}
// 处理发送短信请求
void UserServiceController::handle_send_sms(web::http::http_request request) {
    web::http::http_response response;
    try {
        web::json::value request_body = request.extract_json().get();
        std::string mobile = request_body[U("mobile")].as_string();

        // 调用 RPC 服务发送短信
        user::SendSMSRequest sms_request;
        sms_request.set_mobile(mobile);
        user::WebResponse sms_response;
        grpc::ClientContext context;
        grpc::Status status = stub_->SendSMS(&context, sms_request, &sms_response);

        // 根据 gRPC 的调用结果返回响应
        if (status.ok()) {
            response.set_status_code(web::http::status_codes::OK);
            web::json::value result;
            result[U("code")] = web::json::value::number(sms_response.code());
            result[U("message")] = web::json::value::string(sms_response.message());
            response.set_body(result);
        } else {
            response.set_status_code(web::http::status_codes::BadRequest);
            response.set_body("Error sending SMS.");
        }
    } catch (const std::exception& e) {
        response.set_status_code(web::http::status_codes::BadRequest);
        response.set_body("Invalid request format.");
    }
    request.reply(response);
}
// 处理手机登录请求
void UserServiceController::handle_mobile_login(web::http::http_request request) {
    web::http::http_response response;
    try {
        web::json::value request_body = request.extract_json().get();
        std::string mobile = request_body[U("mobile")].as_string();
        int code = request_body[U("code")].as_integer();

        // 调用 RPC 服务进行手机登录
        user::MobileLoginRequest login_request;
        login_request.set_mobile(mobile);
        login_request.set_code(code);
        user::MobileLoginResponse login_response;
        grpc::ClientContext context;
        grpc::Status status = stub_->MobileLogin(&context, login_request, &login_response);

        // 根据 gRPC 的调用结果返回响应
        if (status.ok()) {
            response.set_status_code(web::http::status_codes::OK);
            web::json::value result;
            result[U("login_success")] = web::json::value::boolean(login_response.login_success());
            result[U("token")] = web::json::value::string(login_response.token());
            result[U("message")] = web::json::value::string(login_response.message());
            response.set_body(result);
        } else {
            response.set_status_code(web::http::status_codes::BadRequest);
            response.set_body("Invalid mobile login credentials.");
        }
    } catch (const std::exception& e) {
        response.set_status_code(web::http::status_codes::BadRequest);
        response.set_body("Invalid request format.");
    }
    request.reply(response);
}

// 处理创建登录 Token 请求
void UserServiceController::handle_create_login_token(web::http::http_request request) {
    web::http::http_response response;
    try {
        web::json::value request_body = request.extract_json().get();
        int64_t user_id = request_body[U("user_id")].as_integer();

        // 调用 RPC 服务创建登录 Token
        user::CreateLoginTokenRequest token_request;
        token_request.set_user_id(user_id);
        user::CreateLoginTokenResponse token_response;
        grpc::ClientContext context;
        grpc::Status status = stub_->CreateLoginToken(&context, token_request, &token_response);

        // 根据 gRPC 的调用结果返回响应
        if (status.ok()) {
            response.set_status_code(web::http::status_codes::OK);
            web::json::value result;
            result[U("token")] = web::json::value::string(token_response.token());
            response.set_body(result);
        } else {
            response.set_status_code(web::http::status_codes::BadRequest);
            response.set_body("Error creating login token.");
        }
    } catch (const std::exception& e) {
        response.set_status_code(web::http::status_codes::BadRequest);
        response.set_body("Invalid request format.");
    }
    request.reply(response);
}
void RunHTTPServer(std::shared_ptr<UserServiceController> controller) {
    uri_builder uri(U("http://localhost:8080"));
    auto addr = uri.to_uri().to_string();
    http_listener listener(addr);

    listener.support(methods::POST, [controller](http_request request) {
        // 在响应中添加CORS头
        web::http::http_response response;
        response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
        response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
        response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));

        // 路由到不同的处理方法
        if (request.request_uri().path() == U("/user/queryUser")) {
            controller->handle_query_user(request);
        } else if (request.request_uri().path() == U("/user/sendSMS")) {
            controller->handle_send_sms(request);
        } else if (request.request_uri().path() == U("/user/mobileLogin")) {
            controller->handle_mobile_login(request);
        } else if (request.request_uri().path() == U("/user/createLoginToken")) {
            controller->handle_create_login_token(request);
        } else {
            response.set_status_code(web::http::status_codes::NotFound);
            response.set_body("Not Found");
            request.reply(response);
        }
    });

    try {
        listener
            .open()
            .then([addr]() { std::cout << "Listening at: " << addr << std::endl; })
            .wait();

        std::cout << "Server is running, waiting for requests..." << std::endl;

        // 让服务器持续运行，直到被显式停止
        std::this_thread::sleep_for(std::chrono::hours(24)); // 设定服务器最多运行 24 小时
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

