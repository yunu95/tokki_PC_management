#include "DBManager.h"
#include "Member.h"
DBManager* DBManager::instance = nullptr;

bool DBManager::Register(char * name, char * age, char * phonenum, char * id, char * passwd, char* question, char* psw_answer)
{
	char message[100];
	char buffer[100];
	snprintf(message, 100, "m|%s|%s|%s|%s|%s|%s|%s", name, age, phonenum, id, passwd, question, psw_answer);
	//printf("[client] : ");
	//scanf("%s", say);
	send(clientsock, message, (int)strlen(message), 0);//발신

													   /* message : 서버로부터 받아온 값
													   strleng : 서버로부터 받아온 값의 길이 */

	int strleng = recv(clientsock, buffer, sizeof(message) - 1, 0);//수신
	if (strleng == -1)
	{
		printf(" 메세지 수신 실패 ");
	}
	buffer[strleng] = '\0';

	return buffer[0] != '0';
}
bool DBManager::Shutdown(char* id, int used_time)
{//***종료
	char message[100];
	char buffer[100];
	sprintf(message, "s|%s|%d", id, used_time);
	send(clientsock, message, strlen(message) + 1, 0);
	// it receives 
	int strleng = recv(clientsock, buffer, 100, 0);//수신
	return buffer[0] != '0';
}
bool DBManager::Register(char* WholeMessage)
{//***회원가입
	char buffer[101];
	int temp;
	send(clientsock, WholeMessage, temp = strlen(WholeMessage) + 1, 0);
	// it receives 
	int strleng = recv(clientsock, buffer, 100, 0);//수신
	if (strleng == -1)
	{
		printf(" 메세지 수신 실패 ");
	}
	return buffer[0] != '0';
}
bool DBManager::AddTime(char * id, int time)
{//***시간추가
	char message[100];
	char buffer[100];
	snprintf(message, 100, "r|%s|%s", id, time);
	//printf("[client] : ");
	//scanf("%s", say);
	send(clientsock, message, (int)strlen(message), 0);//발신

													   /* message : 서버로부터 받아온 값
													   strleng : 서버로부터 받아온 값의 길이 */
	while (true)
	{
		/*
		여기에 답변포맷대로 오는지 확인하고 받는것 넣기
		*/
		int strleng = recv(clientsock, buffer, sizeof(message) - 1, 0);//수신
		if (strleng == -1)
		{
			printf(" 메세지 수신 실패 ");
		}
		buffer[strleng] = '\0';
		if (strncmp(buffer, "          ", 10) == 0)
			break;
	}
	return false;
}
//format : l|(id-c)|(password-c)
char* DBManager::Login(char* wholeMessage)
{//***만든 메세지포맷을 서버로 보내는 함수(왜있는지모르겠음)
	char buffer[100];
	//printf("[client] : ");
	//scanf("%s", say);
	send(clientsock, wholeMessage, (int)strlen(wholeMessage) + 1, 0);//발신
	int strleng = recv(clientsock, buffer, 99, 0);//수신
	return buffer;
}
char* DBManager::Login(char* id, char* password)
{//로그인을 메세지포맷대로 만드는 함수(왜있는지모르겠음)
	char message[1024];
	snprintf(message, 1024, "l|%s|%s", id, password);
	return Login(message);
}
char* DBManager::Login(char* id, char* password, int* left_time)
{//로그인
	char* ret_value = Login(id, password);
	if (strcmp(ret_value, "0") == 0)//로그인실패
		return "false";
	char* minute;
	char* seconds;
	minute = ret_value;
	for (seconds = ret_value; *seconds != ':'; seconds++);
	*seconds = '\0';
	seconds++;
	*left_time = (atoi(minute)) * 60 + (atoi(seconds));
	return ret_value;
}
DBManager* DBManager::GetInstance()
{//싱글톤~~~~~~
	if (instance)
		return instance;
	else
		return instance = new DBManager();
}
DBManager::DBManager()
{//디비와 소켓통신
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("초기화 실패\n");
		exit(1);
	}
	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientsock == INVALID_SOCKET)
	{
		printf("소켓 생성 실패\n");
		exit(1);
	}
	memset(&sockinfo, 0, sizeof(sockinfo));

	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(PORT);
	sockinfo.sin_addr.s_addr = inet_addr(IP);
	if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
	{
		printf(" 서버 접속 실패 ");
		exit(1);
	}
}



DBManager::~DBManager()
{
	closesocket(clientsock);
	WSACleanup();
}

bool DBManager::Recharge(char * id, char * time)
{//충전
	char message[100];
	char buffer[100];
	sprintf(message, "r|%s|%s", id, time);//메세지포맷
	send(clientsock, message, (int)strlen(message) + 1, 0);//발신
	int strleng = recv(clientsock, buffer, 99, 0);//수신

	if (strcmp(buffer, "0") == 0)
		return false;//충전실패(아이디가 틀림)
	else
		return true;//충전성공
}
char* DBManager::ShowTime(char*id)
{//시간보여주기
	char message[100];
	char bufer[100] = { "" };
	sprintf(message, "lp|%s", id);
	send(clientsock, message, (int)strlen(message) + 1, 0);//발신
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//수신
	return bufer;
}
bool DBManager::ChangePassword(char*m)
{//비밀번호바꾸기
	char mess[1024] = { "" };
	char bufer[100] = { "" };
	strcpy(mess, m);
	send(clientsock, mess, (int)strlen(mess) + 1, 0);//발신
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//수신
	if (bufer[0] == '0')
		return false;//아이디가 틀렸거나 비밀번호가틀렸거나
	else
		return true;//성공
}
char* DBManager::Question(char*m)
{//비밀번호확인질문
	char mess[20] = { "" };
	char bufer[100] = { "" };
	strcpy(mess, m);
	send(clientsock, mess, (int)strlen(mess) + 1, 0);//발신
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//수신

	return bufer;//질문
}
bool DBManager::Answer(char*m)
{//비밀번호확인질문 정답
	char mess[50] = { "" };
	char bufer[100] = { "" };
	strcpy(mess, m);
	send(clientsock, mess, (int)strlen(mess) + 1, 0);//발신
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//수신

	if (bufer[0] == '0')
		return false;//틀림
	else
		return true;//맞음(비밀번호바뀜)
}
