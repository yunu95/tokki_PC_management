#include<iostream>
#include<cstdio>
#include<mysql/mysql.h>
#include<string.h>
//#include<my_global.h>
#include<stdlib.h>
//#include<conio.h>
#define HOST "127.0.0.1"//host address
#define USER "root"//user name
#define PASS "dna12345"//password
#define NAME "test"//db name
#define POTE 3306//port
using namespace std;

class Mysql
{
	char query[255];//query
	int len;
	MYSQL *conn_ptr; //MYSQL connect variable
	MYSQL_RES *res;//query result variable
	MYSQL_ROW row;//query's real data value
public:
	void Connect();
	bool membership(char* name,int age,char* phonenum,char* id,char* password,char* psw_question,char* psw_answer);
	bool login(char* id,char* password);
	void DisConnect(MYSQL_RES* r, MYSQL* c);
};
