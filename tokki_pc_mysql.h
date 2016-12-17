#include<iostream>
#include<cstdio>
#include<ctime>
#include<time.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string>
#include<string.h>
#include"sha256.h"
#define HOST "127.0.0.1"//host address
#define USER "root"//user name
#define PASS "dna12345"//password
#define NAME "test"//db name
#define POTE 3306//port

using namespace std;

class Mysql
{
	char query[1024];//query
	int len;
	MYSQL *conn_ptr; //MYSQL connect variable
	MYSQL_RES *res;//query result variable
	MYSQL_ROW row;//query's real data value
	char t[80];
public:
	void Connect();
	bool membership(char* name, int age, char* phonenum, char* id, char* password, char* psw_question, char* psw_answer, char*email);
	char* current_datetime();
	char* login(char* id, char* password);
	char* recharge(char* id, int rechargetime);
	char* LeftTimeShow(char* id);
	char* ShutDown(char*id, int usingtime);
	bool ChangePsw(char*id, char*orignpsw, char*newpsw);
	char* Find_question(char*id);
	bool Find_answer(char* id, char* answer);
	char* Random_psw();
	void DisConnect(MYSQL_RES* r, MYSQL* c);
};
