#include"tokki_pc_mysql.h"

void Mysql::Connect()
{//Connect to MYSQL!
	conn_ptr = mysql_init(NULL);//init
	if (!conn_ptr)
	{
		printf("mysql_init failed!!\n");
	}
	/*Connect to mysql*/
	conn_ptr = mysql_real_connect(conn_ptr, HOST, USER, PASS, NAME, POTE, (char*)NULL, 0);
	if (conn_ptr)
	{
		printf("connected! \n");
		mysql_query(conn_ptr, "set names euckr");
	}
	else
		printf("FAIL! \n");
	printf("mysql client version : %s\n", mysql_get_client_info());
}

bool Mysql::membership(char* name,int age,char* phonenum,char* id,char* password,char* psw_question,char* psw_answer)
{
	sprintf(query,"select from UserInfo where id='%s'",id);
	len = mysql_query(conn_ptr, query);//run query
	res = mysql_store_result(conn_ptr);//query value
	
	if(res->row_count==0)
	{//memvership(register)
		sprintf(query, "insert into UserInfo values ('%s','%d','%s','%s','%s','%s','%s')", name,age,phonenum,id,password,psw_question,psw_answer);
		len=mysql_query(conn_ptr, query);
		return true;
	}
	else
	{//id is already exist
		return false;
	}
}

bool Mysql::login(char* id,char* pass)
{
	sprintf(query, "select password from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	if (res->row_count == 0)
	{//id not found
		return false;
	}
	
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		if (strcmp(row[0],pass)==0)
		{//login success
			return true;
		}
	}
	return false;//incorrect password
}
void Mysql::DisConnect(MYSQL_RES* r, MYSQL* c)
{//disconnect mysql
	mysql_free_result(r);//free res
	mysql_close(c);//close
}
