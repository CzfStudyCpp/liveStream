#ifndef __REDISCONNECTION_H_
#define __REDISCONNECTION_H_

#include <hiredis/hiredis.h>
#include <string>
#include <iostream>
#include <assert.h>

class RedisConnection {
public:
    RedisConnection();
    ~RedisConnection();

    // 连接到 Redis 服务器
    bool Connect(const std::string& host, int port);

    // 执行一个简单的命令并返回结果
    bool Execute(const std::string& command);

    // 获取某个键的值（对于 GET 命令）
    bool Get(const std::string& key, std::string& value);

    // 设置一个键的值（对于 SET 命令）
    bool Set(const std::string& key, const std::string& value);

    // 设置一个键的值并指定过期时间（单位：秒）
    bool SetWithExpire(const std::string& key, const std::string& value, int expireTimeInSec);

    // 返回错误信息
    const char* GetErrInfo();

    // 关闭连接
    void Close();

private:
    redisContext* m_pContext;  // Redis连接
    std::string m_errMsg;       // 错误信息
};

#endif // !__REDISCONNECTION_H_
