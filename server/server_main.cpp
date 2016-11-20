#define _CRT_SECURE_NO_WARNINGS
#pragma comment (lib , "ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>
#include <process.h>

void __cdecl RecvThread (void * p)
{
	SOCKET sock = (SOCKET)p;
	char buf[256];
	while(1)
	{
		//-----------Ŭ���̾�Ʈ�κ��� ����------------
		int recvsize = recv(sock,buf,sizeof(buf),0);
		if(recvsize <= 0)
		{
			printf("��������\n");
			break;
		}
		//------------------------------------------------
		buf[recvsize] = '\0';
		printf("client >> %s\n",buf);
		//----------Ŭ���̾�Ʈ���� ����------------------
		int sendsize = send(sock,buf,strlen(buf),0);
		if(sendsize <= 0)
			break;
		//-----------------------------------------------
	}
	//-----------���� �ݱ�---------------
	closesocket(sock);
	//------------------------------------
}

int main()
{
	//-------���� ���̺귯�� �ҷ�����(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(retval != 0)
	{
		printf("WSAStartup() Error\n");
		return 0;
	}
	//-------------------------------------------

	//----------���� ����--------------
	SOCKET serv_sock;
	serv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock == SOCKET_ERROR)
	{
		printf("socket() Error\n");
		return 0;
	}
	//-----------------------------------

	//--------����(�ڽ�)�� ���� ���� �Է�------------
	SOCKADDR_IN serv_addr = {0};					// �ʱ�ȭ
	serv_addr.sin_family = AF_INET;					// IP ���
	serv_addr.sin_port = htons(4000);				// ��Ʈ 4000��
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// �ּҴ� �˾Ƽ� ã��
	//------------------------------------------------

	//-----------���ͳݿ� ����---------------------
	retval = bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(SOCKADDR));
	if(retval == SOCKET_ERROR)
	{
		printf("bind() Error\n");
		return 0;
	}
	//--------------------------------------------

	//-----------����ο� ����-----------------
	listen(serv_sock,5);		// 5������� ����� �� �ְ� ��...
	//-------------------------------------------
	SOCKADDR_IN clnt_addr = {0};
	int size = sizeof(SOCKADDR_IN);
	
	while(1)
	{
		//-------------Ŭ���̾�Ʈ ���� ���, connect�� �ϸ� ������-------------
		SOCKET clnt_sock = accept(serv_sock,(SOCKADDR*)&clnt_addr,&size);
		if(clnt_sock == SOCKET_ERROR)
		{
			printf("accept() Error\n");
			continue;
		}
		//----------------------------------------------------------------------
		printf("Ŭ���̾�Ʈ ����\n");
		printf("IP : %s, Port : %d\n",inet_ntoa(clnt_addr.sin_addr),clnt_addr.sin_port);
		//-----------���� ������ ����-------------
		_beginthread(RecvThread,NULL,(void*)clnt_sock);
		//-----------------------------------------
	}
	//----------���� ����---------------
	closesocket(serv_sock);
	//-----------------------------------

	//-------���̺귯�� ����(?)---------
	WSACleanup();
	//----------------------------------
}