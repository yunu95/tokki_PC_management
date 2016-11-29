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
                    char *command;
					memset(buf,'\0',1024);
					str_len = read(i, buf, BUF_SIZE);
					printf("buf : %s strlen : %d\n",buf,str_len);
					command=strtok(buf,"|");
					
					if (str_len <= 0)
					{//receive close signal
						FD_CLR(i, &reads);
						close(i);
						printf("close client : %d \n", i);
					}
					else if(strcmp(command,"l")==0)
					{//log in
                        char *id=strtok(NULL,"|");
                        char *psw=strtok(NULL,"|");
						char *result;
						if(result=db.login(id,psw))
							write(i,result,strlen(result));
						else
							write(i,"0",3);
					}
					else if(strcmp(command,"m")==0)
					{//membership(register)
						char *name=strtok(NULL,"|");
						int age=atoi(strtok(NULL,"|"));
						char *phonenum=strtok(NULL,"|");
						char *id=strtok(NULL,"|");
						char *password=strtok(NULL,"|");
						char *psw_question=strtok(NULL,"|");
						char *psw_answer=strtok(NULL,"|");
						char *email=strtok(NULL,"|");
						
						if(db.membership(name,age,phonenum,id,password,psw_question,psw_answer,email))
						{
							write(i,"1",5);
						}
						else
							write(i,"0",6);
					}
					else if(strcmp(command,"r")==0)
					{//recharge
						char *id=strtok(NULL,"|");
						int rc=atoi(strtok(NULL,"|"));
						printf("id : %s  rc : %d\n",id,rc );
						char *result;
						if(result=db.recharge(id,rc))
						{
							write(i,result,strlen(result));
						}
						else
							write(i,"0",2);
					}
					else if(strcmp(command,"lp")==0)
					{//show left time
						char *id=strtok(NULL,"|");
						
						char *result;
						if(result=db.LeftTimeShow(id))
						{
							write(i,result,strlen(result));
						}
						else
							write(i,"0",2);
					}
					else if(strcmp(command,"s")==0)
					{//shutdown
						char *id=strtok(NULL,"|");
						int ut=atoi(strtok(NULL,"|"));//using time
						
						printf("id : %s  rc : %d\n",id,ut );
						
						char *result;
						
						if(result=db.ShutDown(id,ut))
						{
							write(i,result,strlen(result));
						}
						else
							write(i,"0",2);
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
	
}
