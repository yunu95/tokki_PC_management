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
		//-----------클라이언트로부터 수신------------
		int recvsize = recv(sock,buf,sizeof(buf),0);
		if(recvsize <= 0)
		{
			printf("접속종료\n");
			break;
		}
		//------------------------------------------------
		buf[recvsize] = '\0';
		printf("client >> %s\n",buf);
		//----------클라이언트에게 전송------------------
		int sendsize = send(sock,buf,strlen(buf),0);
		if(sendsize <= 0)
			break;
		//-----------------------------------------------
	}
	//-----------소켓 닫기---------------
	closesocket(sock);
	//------------------------------------
}

int main()
{
	//-------소켓 라이브러리 불러오기(?)--------
	WSADATA wsaData;
	int retval = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(retval != 0)
	{
		printf("WSAStartup() Error\n");
		return 0;
	}
	//-------------------------------------------

	//----------소켓 생성--------------
	SOCKET serv_sock;
	serv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(serv_sock == SOCKET_ERROR)
	{
		printf("socket() Error\n");
		return 0;
	}
	//-----------------------------------

	//--------서버(자신)의 소켓 정보 입력------------
	SOCKADDR_IN serv_addr = {0};					// 초기화
	serv_addr.sin_family = AF_INET;					// IP 사용
	serv_addr.sin_port = htons(4000);				// 포트 4000번
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 주소는 알아서 찾기
	//------------------------------------------------

	//-----------인터넷에 연결---------------------
	retval = bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(SOCKADDR));
	if(retval == SOCKET_ERROR)
	{
		printf("bind() Error\n");
		return 0;
	}
	//--------------------------------------------

	//-----------대기인원 설정-----------------
	listen(serv_sock,5);		// 5명까지만 대기할 수 있게 함...
	//-------------------------------------------
	SOCKADDR_IN clnt_addr = {0};
	int size = sizeof(SOCKADDR_IN);
	
	while(1)
	{
		//-------------클라이언트 접속 대기, connect를 하면 리턴함-------------
		SOCKET clnt_sock = accept(serv_sock,(SOCKADDR*)&clnt_addr,&size);
		if(clnt_sock == SOCKET_ERROR)
		{
			printf("accept() Error\n");
			continue;
		}
		//----------------------------------------------------------------------
		printf("클라이언트 접속\n");
		printf("IP : %s, Port : %d\n",inet_ntoa(clnt_addr.sin_addr),clnt_addr.sin_port);
		//-----------수신 스레드 생성-------------
		_beginthread(RecvThread,NULL,(void*)clnt_sock);
		//-----------------------------------------
	}
	//----------소켓 닫음---------------
	closesocket(serv_sock);
	//-----------------------------------

	//-------라이브러리 해제(?)---------
	WSACleanup();
	//----------------------------------
}