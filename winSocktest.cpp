#include<WinSock2.h>
#include<cstdio>
#include<iostream>
#define PORT 8024
#define IP "210.94.181.91"
using namespace std;

int main(int argc,char*argv[])
{

	SOCKET clientsock;
	WSADATA wsa;
	struct sockaddr_in sockinfo;
	char message[30];
	int strlen;

	//if (argc != 3)
	//{
	//	printf("usage : %s <ip> <port>\n", argv[0]);
	//	exit(1);
	//}

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		printf("초기화 실패\n");

	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientsock == INVALID_SOCKET)
		printf("소켓 생성 실패\n");

	memset(&sockinfo, 0, sizeof(sockinfo));

	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(PORT);
	sockinfo.sin_addr.s_addr = inet_addr(IP);
	if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
		printf(" 서버 접속 실패 ");
	
	while (1)
	{
		
		char say[300] = { 0 };
		printf("[client] : ");
		scanf("%s", say);

		send(clientsock, say, sizeof(say), 0);
		strlen = recv(clientsock, message, sizeof(message) - 1, 0);
		if (strlen == -1)
			printf(" 메세지 수신 실패 ");

		printf(" Server say: %s \n", message);
	}
	closesocket(clientsock);
	WSACleanup();
}
