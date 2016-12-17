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
bool DBManager::Shutdown(char* id, int used_time)
{//***����
	char message[100];
	char buffer[100];
	sprintf(message, "s|%s|%d", id, used_time);
	send(clientsock, message, strlen(message) + 1, 0);
	// it receives 
	int strleng = recv(clientsock, buffer, 100, 0);//����
	return buffer[0] != '0';
}
bool DBManager::Register(char* WholeMessage)
{//***ȸ������
	char buffer[101];
	int temp;
	send(clientsock, WholeMessage, temp = strlen(WholeMessage) + 1, 0);
	// it receives 
	int strleng = recv(clientsock, buffer, 100, 0);//����
	if (strleng == -1)
	{
		printf(" �޼��� ���� ���� ");
	}
	return buffer[0] != '0';
}
bool DBManager::AddTime(char * id, int time)
{//***�ð��߰�
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
{//***���� �޼��������� ������ ������ �Լ�(���ִ����𸣰���)
	char buffer[100];
	//printf("[client] : ");
	//scanf("%s", say);
	send(clientsock, wholeMessage, (int)strlen(wholeMessage) + 1, 0);//�߽�
	int strleng = recv(clientsock, buffer, 99, 0);//����
	return buffer;
}
char* DBManager::Login(char* id, char* password)
{//�α����� �޼������˴�� ����� �Լ�(���ִ����𸣰���)
	char message[1024];
	snprintf(message, 1024, "l|%s|%s", id, password);
	return Login(message);
}
char* DBManager::Login(char* id, char* password, int* left_time)
{//�α���
	char* ret_value = Login(id, password);
	if (strcmp(ret_value, "0") == 0)//�α��ν���
		return "false";
	char* minute;
	char* seconds;
	minute = ret_value;
	for (seconds = ret_value; *seconds != ':'; seconds++);
	*seconds = '\0';
	seconds++;
	*left_time = (atoi(minute)) * 60 + (atoi(seconds));
	return ret_value;
}
DBManager* DBManager::GetInstance()
{//�̱���~~~~~~
	if (instance)
		return instance;
	else
		return instance = new DBManager();
}
DBManager::DBManager()
{//���� �������
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
{//����
	char message[100];
	char buffer[100];
	sprintf(message, "r|%s|%s", id, time);//�޼�������
	send(clientsock, message, (int)strlen(message) + 1, 0);//�߽�
	int strleng = recv(clientsock, buffer, 99, 0);//����

	if (strcmp(buffer, "0") == 0)
		return false;//��������(���̵� Ʋ��)
	else
		return true;//��������
}
char* DBManager::ShowTime(char*id)
{//�ð������ֱ�
	char message[100];
	char bufer[100] = { "" };
	sprintf(message, "lp|%s", id);
	send(clientsock, message, (int)strlen(message) + 1, 0);//�߽�
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//����
	return bufer;
}
bool DBManager::ChangePassword(char*m)
{//��й�ȣ�ٲٱ�
	char mess[1024] = { "" };
	char bufer[100] = { "" };
	strcpy(mess, m);
	send(clientsock, mess, (int)strlen(mess) + 1, 0);//�߽�
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//����
	if (bufer[0] == '0')
		return false;//���̵� Ʋ�Ȱų� ��й�ȣ��Ʋ�Ȱų�
	else
		return true;//����
}
char* DBManager::Question(char*m)
{//��й�ȣȮ������
	char mess[20] = { "" };
	char bufer[100] = { "" };
	strcpy(mess, m);
	send(clientsock, mess, (int)strlen(mess) + 1, 0);//�߽�
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//����

	return bufer;//����
}
bool DBManager::Answer(char*m)
{//��й�ȣȮ������ ����
	char mess[50] = { "" };
	char bufer[100] = { "" };
	strcpy(mess, m);
	send(clientsock, mess, (int)strlen(mess) + 1, 0);//�߽�
	int strleng = recv(clientsock, bufer, sizeof(bufer) - 1, 0);//����

	if (bufer[0] == '0')
		return false;//Ʋ��
	else
		return true;//����(��й�ȣ�ٲ�)
}