#include<iostream>
#include<cstdio>
#include <stdlib.h>
#include <string.h>
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
	struct timeval timeout;
	fd_set reads, cpy_reads;
	int fd_max, fd_num;
	socklen_t addr_size;
	int i, str_len;
	int argc;
	char* argv;
	Mysql db;
	char buf[BUF_SIZE];
	char *tmp;
public:
	Socket();
	Socket(int argc, char* argv);
	void Start();
	~Socket();
};
