#include "redisConnect.h"

#include <cstring>
RedisConnection::RedisConnection() : m_pContext(nullptr) {}

RedisConnection::~RedisConnection() {
    if (m_pContext) {
        redisFree(m_pContext);
    }
}

// 连接到 Redis 服务器
bool RedisConnection::Connect(const std::string& host, int port) {
    m_pContext = redisConnect(host.c_str(), port);
    if (m_pContext == nullptr || m_pContext->err) {
        m_errMsg = m_pContext ? m_pContext->errstr : "Unable to allocate Redis context";
        return false;
    }
    return true;
}

// 执行一个简单的命令并返回结果
bool RedisConnection::Execute(const std::string& command) {
    redisReply* reply = (redisReply*)redisCommand(m_pContext, command.c_str());
    if (reply == nullptr) {
        m_errMsg = "Failed to execute Redis command";
        return false;
    }

    std::cout << "Reply: " << reply->str << std::endl;  // 输出命令结果

    freeReplyObject(reply);
    return true;
}

// 获取某个键的值（对于 GET 命令）
bool RedisConnection::Get(const std::string& key, std::string& value) {
    redisReply* reply = (redisReply*)redisCommand(m_pContext, "GET %s", key.c_str());
    if (reply == nullptr) {
        m_errMsg = "Failed to execute GET command";
        return false;
    }

    if (reply->type == REDIS_REPLY_STRING) {
        value = reply->str;
    } else {
        value = "";
    }
    freeReplyObject(reply);
    return true;
}

// 设置一个键的值（对于 SET 命令）
bool RedisConnection::Set(const std::string& key, const std::string& value) {
    redisReply* reply = (redisReply*)redisCommand(m_pContext, "SET %s %s", key.c_str(), value.c_str());
    if (reply == nullptr || reply->type != REDIS_REPLY_STATUS || strcmp(reply->str, "OK") != 0) {
        m_errMsg = "Failed to set value in Redis";
        return false;
    }

    freeReplyObject(reply);
    return true;
}

// 设置一个键的值并指定过期时间（单位：秒）
bool RedisConnection::SetWithExpire(const std::string& key, const std::string& value, int expireTimeInSec) {
    redisReply* reply = (redisReply*)redisCommand(m_pContext, "SETEX %s %d %s", key.c_str(), expireTimeInSec, value.c_str());
    if (reply == nullptr) {
        m_errMsg = "Failed to execute SETEX command";
        return false;
    }
    freeReplyObject(reply);
    return true;
}

// 返回错误信息
const char* RedisConnection::GetErrInfo() {
    return m_errMsg.c_str();
}

// 关闭连接
void RedisConnection::Close() {
    if (m_pContext) {
        redisFree(m_pContext);
        m_pContext = nullptr;
    }
}
