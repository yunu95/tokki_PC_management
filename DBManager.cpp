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
{
	char message[100];
	char buffer[100];
	sprintf(message, "s|%s|%d", id, used_time);
	send(clientsock, message, strlen(message) + 1, 0);
	// it receives 
	int strleng = recv(clientsock, buffer, 100, 0);//수신
	return buffer[0] != '0';
}
bool DBManager::Register(char* WholeMessage)
{
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
{
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
{
	static char buffer[100];
	//printf("[client] : ");
	//scanf("%s", say);
	send(clientsock, wholeMessage, (int)strlen(wholeMessage) + 1, 0);//발신
	int strleng = recv(clientsock, buffer, 99, 0);//수신
	return buffer;
}
char* DBManager::Login(char* id, char* password)
{
	char message[1024];
	snprintf(message, 1024, "l|%s|%s", id, password);
	return Login(message);
}
char* DBManager::Login(char* id, char* password, float* left_time)
{
	char* ret_value = Login(id, password);
	if (ret_value[0] == '0')
		return ret_value;	char* minute;
	char* seconds;
	minute = ret_value;
	for (seconds = ret_value; *seconds != ':'; seconds++);
	*seconds = '\0';
	seconds++;
	*left_time = ((float)atoi(minute))*60.0f + ((float)atoi(seconds));
	return ret_value;
}
DBManager* DBManager::GetInstance() {
	if (instance)
		return instance;
	else
		return instance = new DBManager();
}
DBManager::DBManager()
{
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
{
	char message[100];
	char buffer[100];
	sprintf(message, "r|%s|%s", id, time);
	send(clientsock, message, (int)strlen(message) + 1, 0);//발신
	int strleng = recv(clientsock, buffer, 99, 0);//수신
	return buffer[0] != '0';
}

//#include<WinSock2.h>
//#include<cstdio>
//#include<iostream>
//#include<string>
//#include<stdlib.h>
///*포트와 ip주소를 미리 선언(고정)*/
//#define PORT 8027
//#define IP "210.94.181.91"
//#define BUFSIZE 1024
//using namespace std;
//int main(int argc, char*argv[])
//{
//
//	SOCKET clientsock;
//	WSADATA wsa;
//	struct sockaddr_in sockinfo;
//	char message[BUFSIZE];
//	int strleng;
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//	{
//		printf("초기화 실패\n");
//		exit(1);
//	}
//
//	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	if (clientsock == INVALID_SOCKET)
//	{
//		printf("소켓 생성 실패\n");
//		exit(1);
//	}
//
//	memset(&sockinfo, 0, sizeof(sockinfo));
//
//	sockinfo.sin_family = AF_INET;
//	sockinfo.sin_port = htons(PORT);
//	sockinfo.sin_addr.s_addr = inet_addr(IP);
//	if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
//	{
//		printf(" 서버 접속 실패 ");
//		exit(1);
//	}
//	while (1)
//	{
//		char say[300] = { 0 };//서버에 보낼 값
//		printf("[client] : ");
//		scanf("%s", say);
//		send(clientsock, say, (int)strlen(say), 0);//발신
//		if (strcmp(say, "exit") == 0)
//		{
//			break;
//		}
//		/* message : 서버로부터 받아온 값
//		strleng : 서버로부터 받아온 값의 길이 */
//		strleng = recv(clientsock, message, sizeof(message) - 1, 0);//수신
//
//		if (strleng == -1)
//		{
//			printf(" 메세지 수신 실패 ");
//			exit(1);
//		}
//		message[strleng] = '\0';
//
//
//		printf(" [Server] : %s \n", message);
//
//	}
//	closesocket(clientsock);
//	WSACleanup();
//}