#ifndef USER_H
#define USER_H

#include <string>
#include <memory>

#include "dto.h"

class User {
	

public:
    // 构造函数，传入 MySQL 和 Redis 的连接句柄
    User(){
	
	}

    // 获取用户信息
    bool GetUserInfo(int64_t user_id, userInfo &user_info);

    // 生成验证码
    bool GenerateVerificationCode(const std::string& phone, int& code);

    // 验证码登录
    bool VerifyCodeLogin(const std::string& phone, int code, bool& success, std::string& token);

    // 创建登录 Token
    bool CreateLoginToken(int64_t user_id, std::string& token);

    // 验证登录 Token
    bool ValidateLoginToken(const std::string& token);


};

#endif // USER_H
