#ifndef __BUSINESSPROCESSOR_H_
#define __BUSINESSPROCESSOR_H_

#include <memory>
#include"config.h"
#include "sqlConnect.h"
#include "tables.h"


class BusinessProcessor
{
public:
    // BusinessProcessor 类的构造函数
BusinessProcessor()
{
    // 创建 MysqlConnection 对象并初始化
    std::shared_ptr<MysqlConnection> sqlconn = std::make_shared<MysqlConnection>();
    sqlconn->Init(mysqlConfig.hostIp.c_str(), mysqlConfig.port, mysqlConfig.user.c_str(), mysqlConfig.password.c_str(), mysqlConfig.database.c_str());

    // 初始化 sqlTables_ 成员变量
    sqlTables_ = std::make_shared<SqlTables>(sqlconn);  // 这里需要使用赋值符号，而不是括号调用
}


    bool Init()
    {
        printf("数据库初始化......");

        if (!sqlTables_->CreateUserTable())
        {
            printf("创建用户表失败！");
            return false;
        }

        if (!sqlTables_->CreateSmsTable())
        {
            printf("创建短信表失败！");
            return false;
        }

        if (!sqlTables_->CreateUserPhoneTable())
        {
            printf("创建用户手机表失败！");
            return false;
        }

        if (!sqlTables_->CreateCosidMachineTable())
        {
            printf("创建COSID机器表失败！");
            return false;
        }

        if (!sqlTables_->CreateIndexes())
        {
            printf("创建索引失败！");
            return false;
        }

        printf("数据库初始化完成......");
        return true;
    }

private:
   
    std::shared_ptr<SqlTables> sqlTables_;
};

#endif // !__BUSINESSPROCESSOR_H_
