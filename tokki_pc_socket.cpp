#include"tokki_pc_socket.h"

Socket::Socket()
{
	
}
Socket::Socket(int argc,char* argv)
{//reset val
	if (argc != 2) {
		printf("Usage : ./program_name <port>");
	}

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv));

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		perror("bind() error");

	if (listen(serv_sock, 5) == -1)
		perror("listen() error");

	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);
	fd_max = serv_sock;
	
	db.Connect();
}

void Socket::Start()
{//start socket
	while (1)
	{
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 50000;

		if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1) 
		{//check who is changed!
			printf("fd_num : %d\n", fd_num);
			perror("select() error");
			break;
		}

		if (fd_num == 0)//not change
			continue;


		for (i = 0; i<fd_max + 1; i++)
		{
			if (FD_ISSET(i, &cpy_reads))
			{
				printf("fd_num : %d\n", fd_num);
				if (i == serv_sock)
				{//new client!
					printf("putin serv_sock\n");
					addr_size = sizeof(clnt_addr);
					clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_size);
					FD_SET(clnt_sock, &reads);
					if (fd_max < clnt_sock)
						fd_max = clnt_sock;
					printf("serv_sock=%d", serv_sock);
					printf("connected client : %d \n", clnt_sock);
				}
				else
				{
					str_len = read(i, buf, BUF_SIZE);
					tmp=strtok(buf,"|");
					
					if (str_len == 0)
					{//receive close signal
						FD_CLR(i, &reads);
						close(i);
						printf("close client : %d \n", i);
					}
					else if(strcmp(tmp,"l"))
					{//log in
						if(db.login(strtok(NULL,"|"),strtok(NULL,"|")))
							write(i,"true",5);
						else
							write(i,"false",6);
					}
					else if(strcmp(tmp,"m"))
					{//membership(register)
						if(db.membership(strtok(NULL,"|"),atoi(strtok(NULL,"|")),strtok(NULL,"|"),strtok(NULL,"|"),strtok(NULL,"|"),strtok(NULL,"|"),strtok(NULL,"|")))
						{
							write(i,"true",5);
						}
						else
							write(i,"false",6);
					}
					else
					{//echo
						write(i, buf, str_len);
					}
				}
			}
		}
	}
}

Socket::~Socket()
{//close socket
	close(serv_sock);
}
