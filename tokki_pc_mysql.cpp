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
	time_t now = time(0);//current time type save(현재시간을 time_t타입으로 저장)
	struct tm tstruct;
	tstruct = *localtime(&now);
	strftime(t, sizeof(t), "%Y-%m-%d", &tstruct);//YYYY-MM-DD
	return t;
}

bool Mysql::membership(char* name, int age, char* phonenum, char* id, char* password, char* psw_question, char* psw_answer, char* email)
{
	int num;
	sprintf(query, "select count from tablecount");
	len = mysql_query(conn_ptr, query);//run query
	res = mysql_store_result(conn_ptr);//query value
	row = mysql_fetch_row(res);
	num = atoi(row[0]);//total userinfo table row count
	printf("num : %d\n", num);

	sprintf(query, "select password from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);

	printf("ppp\n");
	if (res->row_count == 0)
	{//memvership(register)
		printf("eee");
		char *ct = current_datetime();
		cout << ct << endl;

		sprintf(query, "insert into UserInfo (num,name,age,phonenum,id,password,psw_question,psw_answer,email,left_time,last_time,total_time) values ('%d','%s','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s')", num + 1, name, age, phonenum, id, password, psw_question, psw_answer, email, "00:00", ct, "00:00");
		cout << "query : " << query << endl;
		len = mysql_query(conn_ptr, query);
		printf("ok\n");

		sprintf(query, "update tablecount set count='%d' where count='%d'", num + 1, num);
		len = mysql_query(conn_ptr, query);

		printf("ok2\n");
		return true;
	}
	else
	{//id is already exist
		return false;
	}
}



char* Mysql::login(char* id, char* pass)
{//log in
	printf("%s\n", current_datetime());
	sprintf(query, "select password from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	if (res->row_count == 0)
	{//id not found
		printf("cant find!\n");
		return NULL;
	}

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		printf("in while\n");
		if (strcmp(row[0], pass) == 0)
		{//login success
			char* lefttime;
			sprintf(query, "select left_time from UserInfo where id='%s'", id);
			len = mysql_query(conn_ptr, query);
			res = mysql_store_result(conn_ptr);
			row = mysql_fetch_row(res);

			lefttime = row[0];

			return lefttime;
		}
	}
	return NULL;//incorrect password
}

char* Mysql::recharge(char* id, int rt)
{//recharge time!
	char* lefttime;
	char* resulttime;
	int h = 0, m = 0;
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

	lefttime = row[0];
	if (lefttime != NULL)
	{
		h = atoi(strtok(lefttime, ":"));
		m = atoi(strtok(NULL, ":"));
	}

	h += (m + rt) / 60;
	m = (m + rt) % 60;

	char hh[10];
	char mm[10];
	char temp[10];
	printf("m :%d\n", m);

	sprintf(hh, "%d", h);
	sprintf(mm, "%d", m);

	if (m<10)
	{//min is 0~9
		printf("m :%d mm :%s\n", m, mm);
		sprintf(temp, "0%s", mm);//00~09
		strcpy(mm, temp);
		printf("m :%d mm :%s\n", m, mm);
	}
	printf("hh :%s mm :%s\n", hh, mm);
	sprintf(resulttime, "%s:%s", hh, mm);
	printf("%s", resulttime);

	sprintf(query, "update UserInfo set left_time='%s' where id='%s'", resulttime, id);
	len = mysql_query(conn_ptr, query);

	return resulttime;
}

char* Mysql::LeftTimeShow(char* id)
{//show left time!
	char* lefttime;
	int h, m;
	sprintf(query, "select left_time from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	row = mysql_fetch_row(res);

	lefttime = row[0];

	if (res->row_count == 0)
	{//id not found
		printf("id not found\n");
		return NULL;
	}
	cout << "lefttime : " << lefttime << endl;
	return lefttime;
}

char* Mysql::ShutDown(char* id, int ut)
{//ShutDown!
	char* lefttime;
	char* totaltime;
	int h = 0, m = 0, th = 0, tm = 0;
	char hh[10];
	char mm[10];
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

	lefttime = row[0];

	if (lefttime != NULL)
	{//user's left time
		h = atoi(strtok(lefttime, ":"));
		m = atoi(strtok(NULL, ":"));
	}
	if (h * 60 + m<ut)
	{//exceed
		sprintf(hh, "%s", "00");
		sprintf(mm, "%s", "00");
	}
	else
	{
		h -= ut / 60;
		ut = ut % 60;
		if (m - ut >= 0)
		{
			m = (m - ut) % 60;
		}
		else//m-ut<0
		{
			h--;
			m = 60 + (m - ut);
		}

		char temp[10];
		sprintf(hh, "%d", h);
		sprintf(mm, "%d", m);
		if (m<10)
		{
			printf("m :%d mm :%s\n", m, mm);
			sprintf(temp, "0%s", mm);
			strcpy(mm, temp);
			printf("m :%d mm :%s\n", m, mm);
		}
	}
	sprintf(lefttime, "%s:%s", hh, mm);
	printf("%s", lefttime);

	sprintf(query, "update UserInfo set left_time='%s' where id='%s'", lefttime, id);
	len = mysql_query(conn_ptr, query);

	/*add using time and total time */
	sprintf(query, "select total_time from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	row = mysql_fetch_row(res);
	totaltime = row[0];

	th = atoi(strtok(totaltime, ":"));
	tm = atoi(strtok(NULL, ":"));
	int total = th * 60 + tm + ut;
	printf("total time : %d\n", total);
	sprintf(totaltime, "%d:%d", total / 60, total % 60);
	sprintf(query, "update UserInfo set total_time='%s' where id='%s'", totaltime, id);
	len = mysql_query(conn_ptr, query);

	return lefttime;

}

bool Mysql::ChangePsw(char* id, char*orign, char*newpsw)
{//change password

	sprintf(query, "select password from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	if (res->row_count == 0)
	{//id not found
		return false;
	}

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		if (strcmp(row[0], orign) == 0)
		{//login success

			sprintf(query, "update UserInfo set password='%s' where id='%s'", newpsw, id);
			len = mysql_query(conn_ptr, query);
			return true;
		}
	}
	return false;//incorrect password
}

char* Mysql::Find_question(char*id)
{//find password - question

	char* question;
	int h, m;
	sprintf(query, "select psw_question from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	row = mysql_fetch_row(res);

	question = row[0];

	if (res->row_count == 0)
	{//id not found
		printf("id not found\n");
		return NULL;
	}

	return question;
}
char* Mysql::Random_psw()
{
	string array[62] = { "0","1","2","3","4","5","6","7","8","9",\
		"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","w","x","y","z",\
		"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","W","X","Y","Z" };
	string pass = "";
	srand(time(NULL));
	for (int i = 0; i<8; i++)
	{
		pass += array[rand() % 62];
	}
	printf("new password : %s\n", pass.c_str());

	cout << "sha256 : " << sha256(pass) << endl;
	cout << "\"password\"" << pass.c_str() << endl;
	return (char*)pass.c_str();
}
bool Mysql::Find_answer(char* id, char*answer)
{//find password - answer

	char* newpsw;
	string st_newpsw;
	sprintf(query, "select psw_answer from UserInfo where id='%s'", id);
	len = mysql_query(conn_ptr, query);
	res = mysql_store_result(conn_ptr);
	if (res->row_count == 0)
	{//id not found
		return false;
	}

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		if (strcmp(row[0], answer) == 0)
		{//answer correct
			newpsw = Random_psw();
			st_newpsw = newpsw;
			cout << "st newpsw : " << st_newpsw << endl;
			cout << "newpsw : " << newpsw << endl;

			sprintf(query, "update UserInfo set password='%s' where id='%s'", (char*)sha256(st_newpsw).c_str(), id);
			len = mysql_query(conn_ptr, query);

			char email[30];
			sprintf(query, "select email from UserInfo where id='%s'", id);
			len = mysql_query(conn_ptr, query);
			res = mysql_store_result(conn_ptr);
			row = mysql_fetch_row(res);

			strcpy(email, row[0]);

			int retval;
			string order = "echo \"new password : ( " + st_newpsw + " ) please change your password!!\" | mail -s \"[Tokki_PC] : Change your Password!\" -a \"From : igneoustiger@gmail.com\" " + email;
			cout << "order = " << order << endl;
			retval = system(order.c_str());
			printf("retval = %d\n", retval);
			return true;
		}
	}
	return false;//incorrect answer
}

void Mysql::DisConnect(MYSQL_RES* r, MYSQL* c)
{//disconnect mysql
	mysql_free_result(r);//free res
	mysql_close(c);//close
}
