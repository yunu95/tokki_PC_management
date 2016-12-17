#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "PCManager.h"
#include "PCManager.h"
#include "Member.h" 
#include "PC.h"
#include "DBManager.h"
#define _CRT_SECURE_NO_WARNINGS
#define BUF_SIZE 1024
#pragma comment (lib , "ws2_32.lib")


// these somesome codes below contain everything needed for singletone desgin pattern
// this class pointer is the only instance of this class
PCManager* PCManager::instance = nullptr;

// this method is used to get instance of this class
PCManager* PCManager::GetInstance() {
	//what this condition says is, just like this. instance != nullpointer
	if (instance)
		return instance;
	else
		// 1. constructor gets called just once
		// 2. constructor exists in private field
		return instance = new PCManager();
}
// �̱��� ������ �����ϴ� �κ��Դϴ�. 

// initiates all the commands needed in terminal.
PCManager::PCManager()
{
	commandsList.push_back(std::string("RechargeMember(rm)"));
	commandsList.push_back(std::string("Checkout(c)"));
	commandsList.push_back(std::string("Status(s)"));
	commandsList.push_back(std::string("Quit(q)"));


	// PC ��ü�� �̹� ������ ���°�����. 100���� �ִٰ� �����ϰ� ���� �ȿ� ����ֽ��ϴ�.
	for (int i = 0; i < 100; i++)
		pcs.push_back(new PC(i));

	//�մ��� ����� ���� ������ ���̽����� �ҷ����� �˴ϴ�.
	//-------���� ���̺귯�� �ҷ�����(?)--------
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		printf("WSAStartup() Error\n");
	}
	//-------------------------------------------

	//----------���� ����--------------
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == SOCKET_ERROR)
	{
		printf("socket() Error\n");
	}
	//-----------------------------------

	//--------����(�ڽ�)�� ���� ���� �Է�------------
	serv_addr.sin_family = AF_INET;               // IP ���
	serv_addr.sin_port = htons(80);            // ��Ʈ 4000��
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // �ּҴ� �˾Ƽ� ã��
													 //------------------------------------------------

													 //-----------���ͳݿ� ����---------------------
	retval = bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		printf("bind() Error\n");
	}
	//--------------------------------------------

	//-----------����ο� ����-----------------
	listen(serv_sock, 5);      // 5������� ����� �� �ְ� ��...
							   //-------------------------------------------
	int size = sizeof(SOCKADDR_IN);

	accept_thread = std::thread(&PCManager::KeepAccepting, this);
}
// ����� ���α׷��� ����Ǵ� ������ �ƴ�. ���� �ʵ��� ��

PCManager::~PCManager()
{
	accept_thread.join();
	//----------���� ����---------------
	//for (auto each : RecieveThreads)
	//	each.join();
	for (auto each : clnt_socks)
		closesocket(each);
	closesocket(serv_sock);
	//-----------------------------------

	//-------���̺귯�� ����(?)---------
	WSACleanup();
	//----------------------------------
}
bool PCManager::QueryNextAction() {
	using namespace std;
	cout << "\nCommand List\n";
	for (string each : commandsList) {
		cout << each;
		cout << ",";
	} // commandsList ���

	cout << "\n";
	string command;
	getline(cin, command);
	for (string each : commandsList)
	{
		// �Էµ� ��ɾ ��� �ҹ��ڷ� �ٲ��ش�.
		for (string::iterator EachChar = command.begin(); EachChar < command.end(); EachChar++)
			*EachChar = tolower(*EachChar);

		// Ŀ�ǵ忡 ���� �ʿ��� �Լ��� ȣ���Ѵ�.

		if (command == "rm") {
			//RechargeTime(const Member& target, const float& seconds)
			char id[100];
			char time[100];
			cout << "��� ���̵� �Է��Ͻÿ�\n";
			scanf("%s", id);
			cout << "��� �������� �Է��Ͻÿ�.\n";
			scanf("%s", time);
			if (DBManager::GetInstance()->Recharge(id, time))
			{
				cout << "���� �Ϸ�!\n";
				return true;
			}
			else
			{
				cout << "���� ����. ���̵� ��Ȯ���Ͻÿ�.\n";
				return false;
			}
		}

		if (command == "s")
		{
			//PC ����Ȯ���� ���� PC���� pc�� �� �� �밡 ���� �ְ� ��밡 ���� �ִ���, -  is_power_on
			//�� �� �밡 ��������� pc���� ���¸� �����ش�. - is_active
			// ���ͷ����ͷ� ���Ϳ��� �� �� ���� �� ������ �����մϴ�.

			LoadPCinfos(); // PC�� ������ ���� �ݴϴ�. 

			int On_count = 0;
			int OFF_count = 0;
			int active_count = 0;

			for (auto status = pcs.begin(), end = pcs.end(); status != end; ++status) {
				if ((**status).GetPower_Status() == true)
					On_count++;

				else
					OFF_count++;

				if ((**status).Getactive_Status() == true)
					active_count++;
			}

			cout << "���� ���� �ִ� PC�� ����� " << On_count << " �� �Դϴ�." << endl;
			cout << "���� ���� �ִ� PC�� ����� " << OFF_count << " �� �Դϴ�." << endl;
			cout << "���� ���ǰ� �ִ� PC�� ����� " << active_count << " �� �Դϴ�." << endl;

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			return true;
		}
		if (command == "q") {
			return false;
		}
	}
	cout << "UnIdentified Command\n";
	return true;
}
void PCManager::Initialize() {

	while (QueryNextAction());
}


void PCManager::RechargeTime(const Member& target, const float& seconds)
{
	// ��� ���̵� �䱸�ϰ�, ���̵� ������ DB���� �ҷ��ɴϴ�.

	// below here should be placed socket programming things
	// which means, Back to work! sung yeon!

	// ������ �ִ� left_time�� seconds�� ���ؼ� �����մϴ�.
}

void PCManager::LoadPCinfos()
{
	using namespace std;
	string inputString;

	ifstream inputFile("PCinfos.txt"); // PCinfos ���� PC�濡 �ִ� PC���� ������ ����ֽ���. 

	while (!inputFile.eof())
	{
		inputFile >> inputString;
		cout << "PC���� ���� : " << inputString << endl;
	}
	inputFile.close();
}


void PCManager::KeepAccepting()
{
	int size = sizeof(SOCKADDR_IN);
	SOCKET clnt_sock;
	SOCKADDR_IN clnt_addr = { 0 };
	while (true)
	{
		clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &size);
		clnt_socks.push_back(clnt_sock);
		RecieveThreads.push_back(
			std::thread([](SOCKET ClientSocket, SOCKADDR *client_address, int* SIZE, std::vector<PC*>& pcs)
		{
			PC* pc;
			while (true)
			{
				char buf[BUF_SIZE + 1];
				char message[100];
				int recvsize = recv(ClientSocket, buf, BUF_SIZE, 0);
				if (recvsize <= 0)
				{
					printf("fail code %d\n", recvsize);
					break;
				}
				buf[recvsize] = '\0';
				// �޼��� �޴°ͱ��� ������� ����
				// ���⼭���ʹ� ��
				PCManager::GetInstance()->DealWithMessage(ClientSocket, client_address, &pc, buf);


			}
		}, clnt_sock, (SOCKADDR*)&clnt_addr, &size, pcs)
		);
		if (clnt_sock == SOCKET_ERROR)
		{
			printf("accept() Error\n");
			exit(0);
		}
		//----------------------------------------------------------------------
		printf("Ŭ���̾�Ʈ ����\n");
		printf("IP : %s, Port : %d\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
	}
}

bool PCManager::DealWithMessage(SOCKET ClientSocket, SOCKADDR *client_address, PC** pc, char* message)
{//***������ �޼����� �ְ�޴ºκ�
	char response[100];

	printf("message from client : %s\n", message);
	// report message is like this
	// "report     %1d%3d"
	// first %1d is 1 or 0. it is 1 when it got booted, and when turning off.
	// %3d is a pc number
	if (strncmp(message, "report    ", 10) == 0)
	{

		bool is_starting;
		*pc = pcs[atoi(message + 11)];
		if (message[10] == '1')
		{
			is_starting = true;
			(*pc)->TurnOnComputer();
		}
		else
		{
			is_starting = false;
			(*pc)->TurnOffComputer();
		}
	}
	else if (strncmp(message, "login     ", 10) == 0)
	{//***�α���
		char* id = message + 10;
		char* pswd = nullptr;
		for (char* i = message + 10; true; i++)
		{
			if (*i == ';')
				if (pswd)
				{
					*i = '\0';
					break;
				}
				else
				{
					*i = '\0';
					pswd = i + 1;
				}
		}
		int leftsecs;
		char * temp = DBManager::GetInstance()->Login(id, pswd, &leftsecs);
		if (strcmp(temp, "false") != 0)
		{//***�α��μ���
			time_t curtime;
			struct tm *curtm;//***����ð��� ���� �ð�����ü
			curtime = time(NULL);
			curtm = localtime(&curtime);//***�� ������ ���� �ð��� ����ü�� ����

										//***����ð��� �ÿ� ������ ���� (�ð�:��)
			std::string nowtime = std::to_string(curtm->tm_hour) + ":" + std::to_string(curtm->tm_min);

			(*pc)->StartUsing(new Member(id, nowtime));
			(*pc)->GetUser()->SetLeftTime(leftsecs);//***������ ���� �ð��� ������ü�� ����

			printf("Send retval : %d\n", send(ClientSocket, temp, 100, 0));
			printf("Send retval : %d\n", send(ClientSocket, temp, 100, 0));
		}
		else
		{//***�α��� ����

			send(ClientSocket, temp, 20, 0);
			send(ClientSocket, temp, 20, 0);

		}

	}
	else if (message[0] == 'o')
	{//***�����ֹ�
		strtok(message, "|");
		char*order = strtok(NULL, "|");//***�ֹ��� ������ ��ȣ
		char*number = strtok(NULL, "|");//***�ڸ���ȣ
		char name[30];
		switch (atoi(order))
		{
		case 1:
			strcpy(name, "���� �䳢���");
			break;
		case 2:
			strcpy(name, "�䳢�� ����");
			break;
		case 3:
			strcpy(name, "���䳢 ����");
			break;
		case 4:
			strcpy(name, "��-��");
			break;
		case 5:
			strcpy(name, "�䳢 �Ұ�����");
			break;
		case 6:
			strcpy(name, "��Ÿ�ο���");
			break;
		case 7:
			strcpy(name, "�䳢����");
			break;
		}
		std::cout << number << "�� ���� " << name << "�� �ֹ��ϼ̽��ϴ�." << std::endl;

	}
	else if (strncmp(message, "cs", 2) == 0)
	{//***���� ǥ��
		strtok(message, "|");
		char*t = strtok(NULL, "|");//***����ð�(����ǥ�ñ���� ���������� �ð�)

		char nowtime[6] = { '\0' };
		strcpy(nowtime, (*pc)->GetUser()->GetNowTime());//***������ ��ǻ�͸� �������� �ð��� ������

		char lt[20];//***�����ð� ��� ����
					//***������ ���� �ð��� ��񿡼� ������
		strcpy(lt, DBManager::GetInstance()->ShowTime((char*)((*pc)->GetUser()->GetIdentifier().c_str())));

		int left = atoi(strtok(lt, ":")) * 60 + atoi(strtok(NULL, ":"));//***�����ð��� ������ ȯ��

		(*pc)->GetUser()->SetLeftTime(left);//***������ �����ð��� ����

		std::string dt = Timespan(nowtime, t);//***���ݱ�������ѽð�(Timespan �Լ� : ����ð�-ó�������ѽð�)
		char *Dt = (char*)dt.c_str();
		int usingtime = atoi(strtok(Dt, ":")) * 60 + atoi(strtok(NULL, ":"));//***���ݱ��� ����ѽð��� ������ ȯ��

																			 //***�����̸�|�����ð�-���ݱ�������ѽð� �� pcŬ���̾�Ʈ�� ����
		if ((*pc)->GetUser()->GetLeftTime() - usingtime >= 0)//***����� �� �״�κ�����
			snprintf(response, 100, "%s|%d", (*pc)->GetUser()->GetIdentifier().c_str(), (*pc)->GetUser()->GetLeftTime() - usingtime);
		else//***������ 0�� ����
			snprintf(response, 100, "%s|%d", (*pc)->GetUser()->GetIdentifier().c_str(), 0);

		send(ClientSocket, response, 100, 0);
		send(ClientSocket, response, 100, 0);
	}
	else if (message[0] == 'm')
	{//***ȸ������
		if (DBManager::GetInstance()->Register(message))
		{//***����
			send(ClientSocket, "1", 99, 0);
			send(ClientSocket, "1", 99, 0);
		}
		else
		{//***����
			send(ClientSocket, "000", 99, 0);
			send(ClientSocket, "000", 99, 0);
		}
	}
	else if (message[0] == 'l'&&message[1] == 'p')
	{//***������ �����ð�ǥ��
		strtok(message, "|");
		char*id = strtok(NULL, "|");//***���̵�
		char left[10];
		char time[10];
		strcpy(left, DBManager::GetInstance()->ShowTime(id));//***�����ð��� left�� ����
		int l = atoi(strtok(left, ":")) * 60 + atoi(strtok(NULL, ":"));//***�����ð��� ������ ȯ��
		sprintf(time, "%d", l);//***�����ð��� char*������ ����ȯ
		send(ClientSocket, time, 10, 0);
		send(ClientSocket, time, 10, 0);

	}
	else if (message[0] == 's')
	{//***����
		strtok(message, "|");
		char*t = strtok(NULL, "|");

		char a[6] = { '\0' };
		strcpy(a, (*pc)->GetUser()->GetNowTime());//***ó�������ѽð�

		std::string dt = Timespan(a, t);//***���ݱ�������ѽð�
		char *Dt = (char*)dt.c_str();
		int usingtime = atoi(strtok(Dt, ":")) * 60 + atoi(strtok(NULL, ":"));//***���ݱ��� ����ѽð� ������ ȯ��

		DBManager::GetInstance()->Shutdown((char*)((*pc)->GetUser()->GetIdentifier().c_str()), usingtime);//***����ó��
		return false;
	}
	else if (message[0] == 'c')
	{//***��й�ȣ�ٲٱ�

		if (DBManager::GetInstance()->ChangePassword(message))
		{//***����
			send(ClientSocket, "1", 99, 0);
			send(ClientSocket, "1", 99, 0);
		}
		else
		{//***����
			send(ClientSocket, "000", 99, 0);
			send(ClientSocket, "000", 99, 0);
		}
	}
	else if (message[0] == 'f'&&message[1] == 'a')
	{//***��й�ȣȮ������
		char question[100];
		char tt[100];
		strcpy(question, DBManager::GetInstance()->Question(message));//Ȯ������
		sprintf(tt, "%s%s", "****", question);
		send(ClientSocket, " ", 100, 0);
		send(ClientSocket, tt, 100, 0);
	}
	else if (message[0] == 'f'&&message[1] == 'r')
	{//***��й�ȣȮ������ ����Ȯ��
		if (DBManager::GetInstance()->Answer(message))
		{//***��
			send(ClientSocket, "1", 99, 0);
			send(ClientSocket, "1", 99, 0);
		}
		else
		{//***Ʋ
			send(ClientSocket, "000", 99, 0);
			send(ClientSocket, "000", 99, 0);
		}

	}
	return true;
}
std::string PCManager::Timespan(char*now, char*end)
{//***�ð�����! �ڿ����� ���ڰ� ������ Ŀ���Ѵ�.

 //---FORMAT---
 //now=hour:min
 //end=hour:min

	int nh = atoi(strtok(now, ":"));
	int nm = atoi(strtok(NULL, ":"));
	int eh = atoi(strtok(end, ":"));
	int em = atoi(strtok(NULL, ":"));

	int h, m;
	if (em < nm)
	{
		m = em + 60 - nm;
		h = eh - 1 - nh;
	}
	else
	{
		m = em - nm;
		h = eh - nh;
	}
	std::string span = std::to_string(h) + ":" + std::to_string(m);

	return span;
}