#include "sqlConnect.h"
#include <stdio.h>
#include <cerrno>
MysqlConnection::MysqlConnection(): mysql_(NULL)
{
	mysql_ = (MYSQL*)malloc(sizeof(MYSQL));//MYSQL是C语言版本实现
}

MysqlConnection::~MysqlConnection()
{
	if (mysql_)
	{
		mysql_close(mysql_);
		free(mysql_);
		mysql_ = NULL;
	}
	return;
}

bool MysqlConnection::Init(const char * szHost, int nPort, const char * szUser, const char * szPasswd, const char * szDb)
{
	mysql_ = mysql_init(mysql_);
	if (mysql_ == NULL)
	{
		printf("init mysql failed %s, %d\n", this->GetErrInfo(), errno);
		return false;
	}
	char cAuto = 1;
	//连接选项
	if (mysql_options(mysql_, mysql_option::MYSQL_OPT_RECONNECT, &cAuto) != 0)
	{
		printf("mysql_options MYSQL_OPT_RECONNECT failed\n");
	}
	//连接
	if (mysql_real_connect(mysql_, szHost, szUser, szPasswd, szDb, nPort, NULL, 0) == NULL)
	{
		printf("connect mysql failed %s, %d\n", this->GetErrInfo(), errno);
		return false;
	}
	
	return true;
}

bool MysqlConnection::Execute(const char * szSql)
{
	//如果查询成功，返回0。如果出现错误，返回非0值。
	
	//int len = strlen(szSql);

	/*if (mysql_real_query(mysql_, szSql, strlen(szSql) != 0))
	{
		if (mysql_errno(mysql_) == CR_SERVER_GONE_ERROR)
		{
			Reconnect();
		}
		return false;
	}*/
	
	if (mysql_real_query(mysql_, szSql, strlen(szSql)) != 0)//
	{
		//连接断掉的标识
		if (mysql_errno(mysql_) == CR_SERVER_GONE_ERROR)
		{			
			Reconnect();
		}
		return false;
	}
	return true;
}

bool MysqlConnection::Execute(const char * szSql, SqlRecordSet& recordSet)
{
	if (mysql_real_query(mysql_, szSql, strlen(szSql)) != 0)//
	{
		if (mysql_errno(mysql_) == CR_SERVER_GONE_ERROR)
		{

			Reconnect();
		}
		printf("sql语句[%s]执行失败！\n", szSql);
		return false;
	}

	MYSQL_RES* p_Res = mysql_store_result(mysql_);
	if (!p_Res)
	{
		return false;
	}

	recordSet.SetResult(p_Res);
	
	return true;
}

int MysqlConnection::EscapeString(const char * pSrc, int nSrclen, char * pDest)
{
	if (!mysql_)
	{
		return 0;
	}
	mysql_real_escape_string(mysql_, pDest, pSrc,  nSrclen);
}

void MysqlConnection::close()
{
}

const char * MysqlConnection::GetErrInfo()
{
	return mysql_error(mysql_);
}

void MysqlConnection::Reconnect()
{
	mysql_ping(mysql_);
}