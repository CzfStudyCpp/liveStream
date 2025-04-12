#ifndef _GLO_DEF_H
#define _GLO_DEF_H

#include <string>
#include <string.h>

// 定义 MYSQL_ 结构体配置
struct MYSQL_ {
    std::string user = "czf";                    // user
    std::string password = "CZFtofuture2024.";    // password
    short int port = 3306;                        // port
    std::string database = "live";                // database
    std::string hostIp = "127.0.0.1";             // hostIp
};

// 定义 REDIS_ 结构体配置
struct REDIS_ {
    std::string hostIp = "127.0.0.1";             // hostIp
    short int port = 6379;                        // port
};

// 定义 RedisKeyBuilder 结构体配置
struct RedisKeyBuilder {
    std::string USER_INFO_KEY = "userInfoKey:";        // USER_INFO_KEY
    int userExpiredTime = 4 * 60;                      // userExpiredTime
    std::string VERIFY_CODE_KEY = "verification_code:"; // VERIFY_CODE_KEY
    int verifiCodeExpiredTime = 3 * 60;                // verifiCodeExpiredTime
    int spaceExpiredTime = 2 * 60;                     // spaceExpiredTime
};

// 在头文件中直接定义全局配置变量
inline MYSQL_ mysqlConfig;  // 全局 MySQL 配置变量
inline REDIS_ redisConfig;  // 全局 Redis 配置变量
inline RedisKeyBuilder redisKeys;  // 全局 Redis 键配置

#endif // _GLO_DEF_H
