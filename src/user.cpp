
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "config.h"
#include "sqlConnect.h"  //mysqlconnect
#include "redisConnect.h" //redis
#include "user.h"



// 获取用户信息
bool User::GetUserInfo(int64_t user_id, userInfo &user_info) {
    std::cout << "Querying user with ID: " << user_id << std::endl;

    // 创建 Redis 连接（使用 shared_ptr 管理 Redis 连接）
    std::shared_ptr<RedisConnection> redis_client = std::make_shared<RedisConnection>();
    if (!redis_client->Connect(redisConfig.hostIp, redisConfig.port)) {
        std::cerr << "Failed to connect to Redis: " << redis_client->GetErrInfo() << std::endl;
        return false;
    }

    // 构建 Redis 键
    std::string redis_key = redisKeys.USER_INFO_KEY + std::to_string(user_id);

    // 尝试从 Redis 查询用户信息
    std::string user_info_str;
    if (redis_client->Get(redis_key, user_info_str) && !user_info_str.empty()) {
        user_info = userInfo::from_json(json::parse(user_info_str));
        std::cout << "Found user info in Redis: " << user_info.nick_name << std::endl;
        return true;
    }

    // 如果 Redis 没有找到，查询 MySQL 数据库
    std::shared_ptr<MysqlConnection> sql_conn = std::make_shared<MysqlConnection>();
    sql_conn->Init(mysqlConfig.hostIp.c_str(), mysqlConfig.port, mysqlConfig.user.c_str(), mysqlConfig.password.c_str(), mysqlConfig.database.c_str());

    char sql_query[256];
    sprintf(sql_query, "SELECT * FROM user WHERE user_id = %ld", user_id);
    SqlRecordSet record_set;
    if (!sql_conn->Execute(sql_query, record_set)) {
        std::cerr << "Failed to query user info from database: " << sql_conn->GetErrInfo() << std::endl;
        return false;
    }

    MYSQL_RES* res = record_set.GetResult();
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        user_info.user_id = std::stoll(row[0]);
        user_info.nick_name = row[1];
        user_info.true_name = row[2];
        user_info.avatar = row[3];
        user_info.sex = std::stoi(row[4]);
        user_info.create_time = row[5];
        user_info.update_time = row[6];

        // 将查询到的数据存入 Redis，并设置过期时间
        std::string user_info_json = user_info.to_json().dump();
        redis_client->SetWithExpire(redis_key, user_info_json, redisKeys.userExpiredTime);

        std::cout << "User info found in MySQL and saved to Redis: " << user_info_json << std::endl;
        return true;
    } else {
        std::cout << "User not found in database" << std::endl;
        // 如果 MySQL 中没有该用户，存入空值并设置 Redis 过期时间
        redis_client->SetWithExpire(redis_key, "User not found!", redisKeys.spaceExpiredTime);
        return false;
    }
}

// 生成验证码
bool User::GenerateVerificationCode(const std::string& phone, int& code) {
    std::cout << "Generating verification code for phone: " << phone << std::endl;

    // 创建 Redis 连接（使用 shared_ptr 管理 Redis 连接）
    std::shared_ptr<RedisConnection> redis_client = std::make_shared<RedisConnection>();
    if (!redis_client->Connect(redisConfig.hostIp, redisConfig.port)) {
        std::cerr << "Failed to connect to Redis: " << redis_client->GetErrInfo() << std::endl;
        return false;
    }

    // 随机生成一个验证码
    srand(time(0));  // 设置随机数种子
    code = rand() % 100000;  // 生成 5 位数的验证码
    
    std::cout << "Generated verification code: " << code << std::endl;

    // 存入 Redis 并设置过期时间
    std::string code_key = redisKeys.VERIFY_CODE_KEY + phone;
    redis_client->SetWithExpire(code_key, std::to_string(code), redisKeys.verifiCodeExpiredTime);

    return true;
}

// 验证码登录
bool User::VerifyCodeLogin(const std::string& phone, int code, bool& success, std::string& token) {
    std::cout << "Verifying code for phone: " << phone << std::endl;

    // 创建 Redis 连接（使用 shared_ptr 管理 Redis 连接）
    std::shared_ptr<RedisConnection> redis_client = std::make_shared<RedisConnection>();
    if (!redis_client->Connect(redisConfig.hostIp, redisConfig.port)) {
        std::cerr << "Failed to connect to Redis: " << redis_client->GetErrInfo() << std::endl;
        return false;
    }

    std::string code_key = redisKeys.VERIFY_CODE_KEY + phone;
    std::string stored_code_str;

    if (redis_client->Get(code_key, stored_code_str)) {
        if (!stored_code_str.empty() && std::stoi(stored_code_str) == code) {
            success = true;
            // 生成登录 Token
            token = "token_" + std::to_string(rand() % 100000);  // 模拟生成一个随机 Token
        } else {
            success = false;
        }
    } else {
        success = false;
    }

    return true;
}

// 创建登录 Token
bool User::CreateLoginToken(int64_t user_id, std::string& token) {
    std::cout << "Creating login token for user with ID: " << user_id << std::endl;

    // 创建 Redis 连接（使用 shared_ptr 管理 Redis 连接）
    std::shared_ptr<RedisConnection> redis_client = std::make_shared<RedisConnection>();
    if (!redis_client->Connect(redisConfig.hostIp, redisConfig.port)) {
        std::cerr << "Failed to connect to Redis: " << redis_client->GetErrInfo() << std::endl;
        return false;
    }

    // 生成一个 Token（这里使用简单的 UUID 或者任何随机生成的策略）
    token = "token_" + std::to_string(user_id);

    // 存储到 Redis，并设置过期时间（单位：秒）
    redis_client->SetWithExpire(token, std::to_string(user_id), 300);  // 设置过期时间为 5 分钟

    return true;
}

// 验证登录 Token
bool User::ValidateLoginToken(const std::string& token) {
    std::cout << "Validating login token: " << token << std::endl;

    bool valid = false;

    // 创建 Redis 连接（使用 shared_ptr 管理 Redis 连接）
    std::shared_ptr<RedisConnection> redis_client = std::make_shared<RedisConnection>();
    if (!redis_client->Connect(redisConfig.hostIp, redisConfig.port)) {
        std::cerr << "Failed to connect to Redis: " << redis_client->GetErrInfo() << std::endl;
        return false;
    }

    // 从 Redis 获取 Token 对应的值
    std::string stored_value;
    if (redis_client->Get(token, stored_value)) {
        if (!stored_value.empty()) {
            std::cout << "Token is valid: " << stored_value << std::endl;
            valid = true;
        } else {
            std::cout << "Invalid token!" << std::endl;
        }
    }

    return valid;
}