#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "PCManager.h"
#include "PCManager.h"
#include "Card.h"
#include "Member.h" 
#include "PC.h"
#include "DBManager.h"
#define _CRT_SECURE_NO_WARNINGS
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
	commandsList.push_back(std::string("RechargeCard"));
	commandsList.push_back(std::string("RechargeMember"));
	commandsList.push_back(std::string("Checkout"));
	commandsList.push_back(std::string("Status"));
	commandsList.push_back(std::string("Quit"));

	// ī�� ��ü�� �̸� ������ cards ���� �ȿ� ����ֽ��ϴ�. ī���� ��ȣ�� 1���� ������� �����˴ϴ�.	

	for (int i = 0; i < 100; i++)
		cards.push_back(new Card(i, 0));

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
	serv_addr.sin_port = htons(4000);            // ��Ʈ 4000��
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

	//-------------Ŭ���̾�Ʈ ���� ���, connect�� �ϸ� ������-------------
	//clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &size);
	//if (clnt_sock == SOCKET_ERROR)
	//{
	//	printf("accept() Error\n");
	//	continue;
	//}
	//----------------------------------------------------------------------
	//printf("Ŭ���̾�Ʈ ����\n");
	//printf("IP : %s, Port : %d\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
	//while (true)
	//{
	//	char buf[100];
	//	int recvsize = recv(clnt_sock, buf, sizeof(buf), 0);
	//	if (recvsize <= 0)
	//	{
	//		printf("fail code %d\n", recvsize);
	//		continue;
	//	}
	//	//-------------------------------------------
	//	buf[recvsize] = '\0';
	//	printf("client >> %s\n", buf);
	//}
	//this thread constantly accepts all the incoming client.
	accept_thread = std::thread(&PCManager::KeepAccepting, this);
	//accept_thread = std::thread(
	//	[](int)
	//{
	//	while (true)
	//	{
	//		SOCKET clnt_socket;
	//		clnt_socket = accept()
	//	}
	//},1
	//);
	//-----------���� ������ ����-------------
	//RecvThreads.push_back(std::thread([]() {

	//}));
	//_beginthread(RecvThread[0], NULL, (void*)clnt_sock);
	//-----------------------------------------


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
		if (command == "rechargecard")
		{

			cout << "ī���� �Ϸù�ȣ�� �߰��� �ð��� �Է��ϼ���. " << endl;
			cin >> CardNumber >> PlusTime;

			cout << "����" << cards[CardNumber]->GetCardNo() << "�� ī���"
				<< cards[CardNumber]->GetLeftTime() << "���� �����Դϴ�." << endl;
			RechargeTime(*cards[CardNumber], PlusTime);

			CardNumber = NULL;
			PlusTime = 0.0;

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			return true;
		}
		if (command == "rechargemember") {
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
		if (command == "checkout")
		{
			// checkout - Do initialize information this card.
			cout << "ī���� �Ϸù�ȣ�� �Է��ϼ���. " << endl;
			cin >> CardNumber;
			CheckoutCard(*cards[CardNumber]);
			cout << cards[CardNumber]->GetCardNo() << "�� ī�尡 "
				<< cards[CardNumber]->GetLeftTime() << "�ʷ� �ʱ�ȭ �Ǿ����ϴ�." << endl;

			CardNumber = NULL;

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			return true;
		}
		if (command == "status")
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
		if (command == "quit") {
			return false;
		}
	}
	cout << "UnIdentified Command\n";
	return true;
}
void PCManager::Initialize() {
	while (QueryNextAction());
}

void PCManager::RechargeTime(Card& target, const float& seconds)
{

	// �ճ� : ī�� ��ȣ�� �ð� ���״ϱ� ���ؿ�
	target.PlusLeftTime(seconds);
	// ���� : �� ī���ȣ�� target���̴ϱ� ��ø��� , cards���Ϳ��� target��°�� ������
	std::cout << target.GetCardNo() << "�� ī�忡"
		<< seconds << "�ʰ� �߰� �Ǿ����ϴ�." << std::endl;
	// �ű⿡ �ִ� left_time�� seconds�� ���ؼ� �����ҰԿ�.
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

void PCManager::CheckoutCard(Card& card)
{
	card.SetLeftTime(0);
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
			std::thread([](SOCKET ClientSocket, SOCKADDR *client_address, int* SIZE, std::vector<Card*>& cards, std::vector<PC*>& pcs)
		{
			PC* pc;
			while (true)
			{
				char buf[100];
				char message[100];
				int recvsize = recv(ClientSocket, buf, 100, 0);
				if (recvsize <= 0)
				{
					printf("fail code %d\n", recvsize);
					continue;
				}
				buf[recvsize] = '\0';
				printf("message from client : %s\n", buf);
				// report message is like this
				// "report     %1d%3d"
				// first %1d is 1 or 0. it is 1 when it got booted, and when turning off.
				// %3d is a pc number
				if (strncmp(buf, "report    ", 10) == 0)
				{
					atoi("11");
					bool is_starting;
					pc = pcs[atoi(buf + 11)];
					if (buf[10] == '1')
					{
						is_starting = true;
						pc->TurnOnComputer();
					}
					else
					{
						is_starting = false;
						pc->TurnOffComputer();
					}
				}
				if (strncmp(buf, "login     ", 10) == 0)
				{
					char* id = buf + 10;
					char* pswd = nullptr;
					char buffer[100];
					for (char* i = buf + 10; true; i++)
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
					printf("Send retval : %d",send(ClientSocket, DBManager::GetInstance()->Login(id, pswd), 100, 0));
				}
				if (strncmp(buf, "rcard     ", 10) == 0)
				{
					int card_num = atoi(buf + 10);
					if (cards[card_num]->GetLeftTime() <= 0.0)
					{
						send(ClientSocket, "0", 2, 0);
					}
					else
					{
						pc->StartUsing(cards[card_num]);
						send(ClientSocket, "1", 2, 0);
					}

				}
				if (buf[0] == 'm')
				{
					if (DBManager::GetInstance()->Register(buf))
						send(ClientSocket, "1", 2, 0);
					else
						send(ClientSocket, "0", 2, 0);
				}
			}
		}, clnt_sock, (SOCKADDR*)&clnt_addr, &size, cards, pcs)
			);
		if (clnt_sock == SOCKET_ERROR)
		{
			printf("accept() Error\n");
		}
		//----------------------------------------------------------------------
		printf("Ŭ���̾�Ʈ ����\n");
		printf("IP : %s, Port : %d\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
	}
}
