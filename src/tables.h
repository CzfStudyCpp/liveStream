#ifndef __SQLTABLES_H_
#define __SQLTABLES_H_

#include "sqlConnect.h"
#include <memory>

class SqlTables
{
public:
    SqlTables(std::shared_ptr<MysqlConnection> sqlconn) : sqlconn_(sqlconn) {}

    // 创建用户表
    bool CreateUserTable()
    {
        printf("正在创建用户信息表......");

        const char* pUserTable = R"(
            CREATE TABLE IF NOT EXISTS user (
                user_id BIGINT NOT NULL DEFAULT '-1' COMMENT '用户id',
                nick_name VARCHAR(35) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT '昵称',
                avatar VARCHAR(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT '头像',
                true_name VARCHAR(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin DEFAULT NULL COMMENT '真实姓名',
                sex TINYINT(1) DEFAULT NULL COMMENT '性别 0男，1女',
                create_time DATETIME DEFAULT CURRENT_TIMESTAMP,
                update_time DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
                PRIMARY KEY (user_id)
            ) ENGINE=InnoDB COMMENT='用户基础信息表';
        )";

        if (!sqlconn_->Execute(pUserTable))
        {
            printf("创建用户信息表失败，错误信息：%s", sqlconn_->GetErrInfo());
            return false;
        }

        printf("用户信息表创建成功！");
        return true;
    }

    // 创建短信发送记录表
    bool CreateSmsTable()
    {
        printf("正在创建短信发送记录表......");

        const char* pSmsTable = R"(
            CREATE TABLE IF NOT EXISTS sms (
                id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键id',
                code INT UNSIGNED DEFAULT '0' COMMENT '验证码',
                phone VARCHAR(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT '' COMMENT '手机号',
                send_time DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '发送时间',
                update_time DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
                PRIMARY KEY (id),
                KEY code (code)
            ) ENGINE=InnoDB AUTO_INCREMENT=1 COMMENT='短信发送记录';
        )";

        if (!sqlconn_->Execute(pSmsTable))
        {
            printf("创建短信发送记录表失败，错误信息：%s", sqlconn_->GetErrInfo());
            return false;
        }

        printf("短信发送记录表创建成功！");
        return true;
    }

    // 创建用户手机表
    bool CreateUserPhoneTable()
    {
        printf("正在创建用户手机表......");

        const char* pUserPhoneTable = R"(
            CREATE TABLE IF NOT EXISTS user_phone (
                id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键id',
                phone VARCHAR(200) CHARACTER SET utf8mb3 COLLATE utf8mb3_bin NOT NULL DEFAULT '' COMMENT '手机号',
                user_id BIGINT DEFAULT '-1' COMMENT '用户id',
                status TINYINT DEFAULT '-1' COMMENT '状态(0无效，1有效)',
                create_time DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
                update_time DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
                PRIMARY KEY (id),
                UNIQUE KEY udx_phone (phone),
                KEY idx_user_id (user_id)
            ) ENGINE=InnoDB AUTO_INCREMENT=1 COMMENT='用户手机表';
        )";

        if (!sqlconn_->Execute(pUserPhoneTable))
        {
            printf("创建用户手机表失败，错误信息：%s", sqlconn_->GetErrInfo());
            return false;
        }

       // printf("用户手机表创建成功！");
        return true;
    }

    // 创建 COSID 机器表
    bool CreateCosidMachineTable()
    {
        printf("正在创建COSID机器表......");

        const char* pCosidMachineTable = R"(
            CREATE TABLE IF NOT EXISTS cosid_machine (
                name VARCHAR(100) NOT NULL COMMENT '{namespace}.{machine_id}',
                namespace VARCHAR(100) NOT NULL,
                machine_id INTEGER UNSIGNED NOT NULL DEFAULT 0,
                last_timestamp BIGINT UNSIGNED NOT NULL DEFAULT 0,
                instance_id VARCHAR(100) NOT NULL DEFAULT '',
                distribute_time BIGINT UNSIGNED NOT NULL DEFAULT 0,
                revert_time BIGINT UNSIGNED NOT NULL DEFAULT 0,
                PRIMARY KEY (name)
            ) ENGINE=InnoDB;
        )";

        if (!sqlconn_->Execute(pCosidMachineTable))
        {
            printf("创建COSID机器表失败，错误信息：%s", sqlconn_->GetErrInfo());
            return false;
        }

     //   printf("COSID机器表创建成功！");
        return true;
    }

    // 创建索引
    bool CreateIndexes()
    {
        printf("正在创建索引......");

        const char* pCreateIndexes = R"(
            CREATE INDEX IF NOT EXISTS idx_namespace ON cosid_machine (namespace);
            CREATE INDEX IF NOT EXISTS idx_instance_id ON cosid_machine (instance_id);
        )";

        if (!sqlconn_->Execute(pCreateIndexes))
        {
            printf("创建索引失败，错误信息：%s", sqlconn_->GetErrInfo());
            return false;
        }

       // printf("索引创建成功！");
        return true;
    }

private:
    std::shared_ptr<MysqlConnection> sqlconn_;
};

#endif // !__SQLTABLES_H_
