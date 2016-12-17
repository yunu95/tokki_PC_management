#include<iostream>
#include<cstdio>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include "tokki_pc_mysql.h"

#define BUF_SIZE 1024

using namespace std;

class Socket
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	struct timeval timeout;//timeval동안 기다렸다가 안되면 에러발생함 select에러
	fd_set reads, cpy_reads;//파일디스크립터
	int fd_max, fd_num;//클라이언트번호
	socklen_t addr_size;
	int i, str_len;
	int argc;//main에서 넘어오는 값 2가아니면 포트번호를 입력안한것
	char* argv;//포트번호가 들어있따
	Mysql db;//mysql
	char buf[BUF_SIZE];

public:
	Socket();
	Socket(int argc, char* argv);
	void Start();
	~Socket();
};
