#include "DBManager.h"
#include "Member.h"
DBManager* DBManager::instance = nullptr;

bool DBManager::Register(char * name, char * age, char * phonenum, char * id, char * passwd, char* question, char* psw_answer)
{
	char message[100];
	char buffer[100];
	snprintf(message, 100, "m|%s|%s|%s|%s|%s|%s|%s",name,age,phonenum,id,passwd ,question,psw_answer);
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

bool DBManager::Register(char* WholeMessage)
{
	char buffer[100];
	send(clientsock, WholeMessage, strlen(WholeMessage), 0);
	int strleng = recv(clientsock, buffer, 100, 0);//수신
	if (strleng == -1)
	{
		printf(" 메세지 수신 실패 ");
	}
	return true;
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
Member DBManager::GetMemberinfo(const char* id, const char* password)
{

	char message[100];
	char buffer[100];
	snprintf(message, 100, "l|%s|%s", id, password);
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
		if(strncmp(buffer, "          ", 10) == 0)
			break;
	}
	printf(" [Server] : %s \n", message);
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