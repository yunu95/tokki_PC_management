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

char* Mysql::current_datetime()
{
	time_t now=time(0);//current time type save(현재시간을 time_t타입으로 저장)
	struct tm tstruct;
	tstruct=*localtime(&now);
	strftime(t,sizeof(t),"%Y-%m-%d",&tstruct);//YYYY-MM-DD
	return t;
}

bool Mysql::membership(char* name,int age,char* phonenum,char* id,char* password,char* psw_question,char* psw_answer,char* email)
{
	int num;
	sprintf(query,"select count from tablecount");
	len = mysql_query(conn_ptr, query);//run query
	res = mysql_store_result(conn_ptr);//query value
	row = mysql_fetch_row(res);
	num=atoi(row[0]);//total userinfo table row count
	printf("num : %d\n",num);
	
	sprintf(query,"select * from UserInfo where id='%s'",id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	
	
	if(res->row_count==0)
	{//memvership(register)
		printf("eee");
		char *ct=current_datetime();
		
		sprintf(query, "insert into UserInfo (num,name,age,phonenum,id,password,psw_question,psw_answer,email,last_time) values ('%d','%s','%d','%s','%s','%s','%s','%s','%s','%s')",num+1, name,age,phonenum,id,password,psw_question,psw_answer,email,ct);
		len=mysql_query(conn_ptr, query);
		printf("ok\n");
		
		sprintf(query, "update tablecount set count='%d' where count='%d'",num+1,num);
		len=mysql_query(conn_ptr, query);
		
		printf("ok2\n");
		return true;
	}
	else
	{//id is already exist
		return false;
	}
}



char* Mysql::login(char* id,char* pass)
{//log in
	printf("%s\n",current_datetime());
	sprintf(query, "select password from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	if (res->row_count == 0)
	{//id not found
		return NULL;
	}
	
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		if (strcmp(row[0],pass)==0)
		{//login success
			char* lefttime;
			sprintf(query, "select left_time from UserInfo where id='%s'", id);
			len = mysql_query(conn_ptr, query);
			res = mysql_store_result(conn_ptr);
			row = mysql_fetch_row(res);
	
			lefttime=row[0];
			
			return lefttime;
		}
	}
	return NULL;//incorrect password
}

char* Mysql::recharge(char* id,int rt)
{//recharge time!
	char* lefttime;
	char* resulttime;
	int h=0,m=0;
	sprintf(query, "select left_time from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	
	printf("ddd\n");
	if (res->row_count == 0)
	{//id not found
		printf("false!\n");
		return NULL;
	}
	row = mysql_fetch_row(res);
	
	lefttime=row[0];
	if(lefttime!=NULL)
	{
		h=atoi(strtok(lefttime,":"));
		m=atoi(strtok(NULL,":"));
	}
		
	h+=(m+rt)/60;
	m=(m+rt)%60;

	char hh[10];
	char mm[10];
	char temp[10];
	printf("m :%d\n",m);
	
	sprintf(hh,"%d",h);
	sprintf(mm,"%d",m);
	
	if(m<10)
	{
		printf("m :%d mm :%s\n",m,mm);
		sprintf(temp, "0%s", mm);
		strcpy(mm,temp);
		printf("m :%d mm :%s\n",m,mm);
	}
	printf("hh :%s mm :%s\n",hh,mm);
	sprintf(resulttime, "%s:%s", hh, mm);
	printf("%s",resulttime);
	
	sprintf(query, "update UserInfo set left_time='%s' where id='%s'",resulttime,id);
	len=mysql_query(conn_ptr, query);
	
	return resulttime;
}

char* Mysql::LeftTimeShow(char* id)
{//show left time!
	char* lefttime;
	int h,m;
	sprintf(query, "select left_time from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	row = mysql_fetch_row(res);
	
	lefttime=row[0];
	
	if (res->row_count == 0)
	{//id not found
		printf("id not found\n");
		return NULL;
	}
	
	return lefttime;
}

char* Mysql::ShutDown(char* id,int ut)
{//ShutDown!
	char* lefttime;
	int h=0,m=0;
	sprintf(query, "select left_time from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	
	printf("ddd\n");
	
	if (res->row_count == 0)
	{//id not found
		printf("false!\n");
		return NULL;
	}
	row = mysql_fetch_row(res);
	
	lefttime=row[0];
	
	if(lefttime!=NULL)
	{
		h=atoi(strtok(lefttime,":"));
		m=atoi(strtok(NULL,":"));
	}	
	
	h-=ut/60;
	ut=ut%60;
	if(m-ut>=0)
	{
		m=(m-ut)%60;
	}
	else//m-ut<0
	{
		h--;
		m=60+(m-ut);
	}
	char hh[10];
	char mm[10];
	char temp[10];
	sprintf(hh,"%d",h);
	sprintf(mm,"%d",m);
	if(m<10)
	{
		printf("m :%d mm :%s\n",m,mm);
		sprintf(temp, "0%s", mm);
		strcpy(mm,temp);
		printf("m :%d mm :%s\n",m,mm);
	}
	sprintf(lefttime, "%s:%s", hh, mm);
	printf("%s",lefttime);
	
	sprintf(query, "update UserInfo set left_time='%s' where id='%s'",lefttime,id);
	len=mysql_query(conn_ptr, query);
	
	return lefttime;
	
}

void Mysql::DisConnect(MYSQL_RES* r, MYSQL* c)
{//disconnect mysql
	mysql_free_result(r);//free res
	mysql_close(c);//close
}
