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
	send(clientsock, message, (int)strlen(message), 0);//�߽�

													   /* message : �����κ��� �޾ƿ� ��
													   strleng : �����κ��� �޾ƿ� ���� ���� */

	int strleng = recv(clientsock, buffer, sizeof(message) - 1, 0);//����
	if (strleng == -1)
	{
		printf(" �޼��� ���� ���� ");
	}
	buffer[strleng] = '\0';

	return buffer[0] != '0';
}

bool DBManager::Register(char* WholeMessage)
{
	char buffer[100];
	send(clientsock, WholeMessage, strlen(WholeMessage) + 1, 0);
	// it receives 
	int strleng = recv(clientsock, buffer, 100, 0);//����
	if (strleng == -1)
	{
		printf(" �޼��� ���� ���� ");
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
	send(clientsock, message, (int)strlen(message), 0);//�߽�

													   /* message : �����κ��� �޾ƿ� ��
													   strleng : �����κ��� �޾ƿ� ���� ���� */
	while (true)
	{
		/*
		���⿡ �亯���˴�� ������ Ȯ���ϰ� �޴°� �ֱ�
		*/
		int strleng = recv(clientsock, buffer, sizeof(message) - 1, 0);//����
		if (strleng == -1)
		{
			printf(" �޼��� ���� ���� ");
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
	send(clientsock, wholeMessage, (int)strlen(wholeMessage) + 1, 0);//�߽�
	int strleng = recv(clientsock, buffer, 99, 0);//����
	return buffer;
}
char* DBManager::Login(char* id, char* password)
{
	char message[100];
	snprintf(message, 100, "l|%s|%s", id, password);
	return Login(message);
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
		printf("�ʱ�ȭ ����\n");
		exit(1);
	}
	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientsock == INVALID_SOCKET)
	{
		printf("���� ���� ����\n");
		exit(1);
	}
	memset(&sockinfo, 0, sizeof(sockinfo));

	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(PORT);
	sockinfo.sin_addr.s_addr = inet_addr(IP);
	if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
	{
		printf(" ���� ���� ���� ");
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
	send(clientsock, message, (int)strlen(message) + 1, 0);//�߽�
	int strleng = recv(clientsock, buffer, 99, 0);//����
	return buffer[0] != '0';
}

//#include<WinSock2.h>
//#include<cstdio>
//#include<iostream>
//#include<string>
//#include<stdlib.h>
///*��Ʈ�� ip�ּҸ� �̸� ����(����)*/
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
//		printf("�ʱ�ȭ ����\n");
//		exit(1);
//	}
//
//	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	if (clientsock == INVALID_SOCKET)
//	{
//		printf("���� ���� ����\n");
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
//		printf(" ���� ���� ���� ");
//		exit(1);
//	}
//	while (1)
//	{
//		char say[300] = { 0 };//������ ���� ��
//		printf("[client] : ");
//		scanf("%s", say);
//		send(clientsock, say, (int)strlen(say), 0);//�߽�
//		if (strcmp(say, "exit") == 0)
//		{
//			break;
//		}
//		/* message : �����κ��� �޾ƿ� ��
//		strleng : �����κ��� �޾ƿ� ���� ���� */
//		strleng = recv(clientsock, message, sizeof(message) - 1, 0);//����
//
//		if (strleng == -1)
//		{
//			printf(" �޼��� ���� ���� ");
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