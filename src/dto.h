#ifndef DTO_H_
#define DTO_H_

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace std;
using json = nlohmann::json;

typedef struct user_ {
    int64_t user_id;    // 用户 ID
    string nick_name;   // 昵称
    string true_name;   // 真实姓名
    string avatar;      // 头像
    int32_t sex;        // 性别
    string create_time; // 创建时间
    string update_time; // 更新时间

    // 默认构造函数
    user_() : user_id(0), sex(0) {}

    // 转换为 JSON
    json to_json() const {
        return json{
            {"user_id", user_id},
            {"nick_name", nick_name},
            {"true_name", true_name},
            {"avatar", avatar},
            {"sex", sex},
            {"create_time", create_time},
            {"update_time", update_time}
        };
    }

    // 从 JSON 反序列化
    static user_ from_json(const json& j) {
        user_ u;
        u.user_id = j["user_id"].get<int64_t>();
        u.nick_name = j["nick_name"].get<string>();
        u.true_name = j["true_name"].get<string>();
        u.avatar = j["avatar"].get<string>();
        u.sex = j["sex"].get<int32_t>();
        u.create_time = j["create_time"].get<string>();
        u.update_time = j["update_time"].get<string>();
        return u;
    }
} userInfo; // Only this definition is kept.


#endif