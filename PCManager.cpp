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
// 싱글톤 패턴을 구현하는 부분입니다. 

// initiates all the commands needed in terminal.
PCManager::PCManager()
{
	commandsList.push_back(std::string("RechargeMember(rm)"));
	commandsList.push_back(std::string("Checkout(c)"));
	commandsList.push_back(std::string("Status(s)"));
	commandsList.push_back(std::string("Quit(q)"));


	// PC 객체는 이미 생성된 상태겠지요. 100개가 있다고 가정하고 벡터 안에 집어넣습니다.
	for (int i = 0; i < 100; i++)
		pcs.push_back(new PC(i));

	//손님이 멤버인 경우는 데이터 베이스에서 불러오게 됩니다.
	//-------소켓 라이브러리 불러오기(?)--------
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0)
	{
		printf("WSAStartup() Error\n");
	}
	//-------------------------------------------

	//----------소켓 생성--------------
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == SOCKET_ERROR)
	{
		printf("socket() Error\n");
	}
	//-----------------------------------

	//--------서버(자신)의 소켓 정보 입력------------
	serv_addr.sin_family = AF_INET;               // IP 사용
	serv_addr.sin_port = htons(80);            // 포트 4000번
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // 주소는 알아서 찾기
													 //------------------------------------------------

													 //-----------인터넷에 연결---------------------
	retval = bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(SOCKADDR));
	if (retval == SOCKET_ERROR)
	{
		printf("bind() Error\n");
	}
	//--------------------------------------------

	//-----------대기인원 설정-----------------
	listen(serv_sock, 5);      // 5명까지만 대기할 수 있게 함...
							   //-------------------------------------------
	int size = sizeof(SOCKADDR_IN);

	accept_thread = std::thread(&PCManager::KeepAccepting, this);
}
// 여기는 프로그램이 실행되는 공간이 아님. 단지 필드일 뿐

PCManager::~PCManager()
{
	accept_thread.join();
	//----------소켓 닫음---------------
	//for (auto each : RecieveThreads)
	//	each.join();
	for (auto each : clnt_socks)
		closesocket(each);
	closesocket(serv_sock);
	//-----------------------------------

	//-------라이브러리 해제(?)---------
	WSACleanup();
	//----------------------------------
}
bool PCManager::QueryNextAction() {
	using namespace std;
	cout << "\nCommand List\n";
	for (string each : commandsList) {
		cout << each;
		cout << ",";
	} // commandsList 출력

	cout << "\n";
	string command;
	getline(cin, command);
	for (string each : commandsList)
	{
		// 입력된 명령어를 모두 소문자로 바꿔준다.
		for (string::iterator EachChar = command.begin(); EachChar < command.end(); EachChar++)
			*EachChar = tolower(*EachChar);

		// 커맨드에 따라 필요한 함수를 호출한다.

		if (command == "rm") {
			//RechargeTime(const Member& target, const float& seconds)
			char id[100];
			char time[100];
			cout << "대상 아이디를 입력하시오\n";
			scanf("%s", id);
			cout << "몇분 충전할지 입력하시오.\n";
			scanf("%s", time);
			if (DBManager::GetInstance()->Recharge(id, time))
			{
				cout << "충전 완료!\n";
				return true;
			}
			else
			{
				cout << "충전 실패. 아이디를 재확인하시오.\n";
				return false;
			}
		}

		if (command == "s")
		{
			//PC 상태확인은 현재 PC방의 pc들 중 몇 대가 켜져 있고 몇대가 꺼져 있는지, -  is_power_on
			//또 몇 대가 사용중인지 pc방의 상태를 보여준다. - is_active
			// 이터레이터로 벡터에서 싹 다 훑은 뒤 변수에 저장합니다.

			LoadPCinfos(); // PC의 개수를 보여 줍니다. 

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

			cout << "현재 켜져 있는 PC의 대수는 " << On_count << " 대 입니다." << endl;
			cout << "현재 꺼져 있는 PC의 대수는 " << OFF_count << " 대 입니다." << endl;
			cout << "현재 사용되고 있는 PC의 대수는 " << active_count << " 대 입니다." << endl;

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
	// 멤버 아이디를 요구하고, 아이디 정보를 DB에서 불러옵니다.

	// below here should be placed socket programming things
	// which means, Back to work! sung yeon!

	// 정보에 있는 left_time에 seconds를 더해서 갱신합니다.
}

void PCManager::LoadPCinfos()
{
	using namespace std;
	string inputString;

	ifstream inputFile("PCinfos.txt"); // PCinfos 에는 PC방에 있는 PC들의 정보가 담겨있슴다. 

	while (!inputFile.eof())
	{
		inputFile >> inputString;
		cout << "PC들의 개수 : " << inputString << endl;
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
				// 메세지 받는것까지 스레드로 구현
				// 여기서부터는 콜
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
		printf("클라이언트 접속\n");
		printf("IP : %s, Port : %d\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
	}
}

bool PCManager::DealWithMessage(SOCKET ClientSocket, SOCKADDR *client_address, PC** pc, char* message)
{//***서버와 메세지를 주고받는부분
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
	{//***로그인
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
		{//***로그인성공
			time_t curtime;
			struct tm *curtm;//***현재시간을 담을 시간구조체
			curtime = time(NULL);
			curtm = localtime(&curtime);//***그 지역의 현재 시간을 구조체에 담음

										//***현재시간을 시와 분으로 맞춤 (시간:분)
			std::string nowtime = std::to_string(curtm->tm_hour) + ":" + std::to_string(curtm->tm_min);

			(*pc)->StartUsing(new Member(id, nowtime));
			(*pc)->GetUser()->SetLeftTime(leftsecs);//***유저의 남은 시간을 유저객체에 넣음

			printf("Send retval : %d\n", send(ClientSocket, temp, 100, 0));
			printf("Send retval : %d\n", send(ClientSocket, temp, 100, 0));
		}
		else
		{//***로그인 실패

			send(ClientSocket, temp, 20, 0);
			send(ClientSocket, temp, 20, 0);

		}

	}
	else if (message[0] == 'o')
	{//***음식주문
		strtok(message, "|");
		char*order = strtok(NULL, "|");//***주문한 음식의 번호
		char*number = strtok(NULL, "|");//***자리번호
		char name[30];
		switch (atoi(order))
		{
		case 1:
			strcpy(name, "내가 토끼라면");
			break;
		case 2:
			strcpy(name, "토끼간 순대");
			break;
		case 3:
			strcpy(name, "산토끼 정식");
			break;
		case 4:
			strcpy(name, "콜-라");
			break;
		case 5:
			strcpy(name, "토끼 불고기버거");
			break;
		case 6:
			strcpy(name, "비타민워터");
			break;
		case 7:
			strcpy(name, "토끼덮밥");
			break;
		}
		std::cout << number << "번 님이 " << name << "을 주문하셨습니다." << std::endl;

	}
	else if (strncmp(message, "cs", 2) == 0)
	{//***상태 표시
		strtok(message, "|");
		char*t = strtok(NULL, "|");//***현재시간(상태표시기능을 눌렀을때의 시간)

		char nowtime[6] = { '\0' };
		strcpy(nowtime, (*pc)->GetUser()->GetNowTime());//***유저가 컴퓨터를 켰을때의 시간을 가져옴

		char lt[20];//***남은시간 담는 변수
					//***유저의 남은 시간을 디비에서 가져옴
		strcpy(lt, DBManager::GetInstance()->ShowTime((char*)((*pc)->GetUser()->GetIdentifier().c_str())));

		int left = atoi(strtok(lt, ":")) * 60 + atoi(strtok(NULL, ":"));//***남은시간을 분으로 환산

		(*pc)->GetUser()->SetLeftTime(left);//***유저의 남은시간에 삽입

		std::string dt = Timespan(nowtime, t);//***지금까지사용한시간(Timespan 함수 : 현재시간-처음시작한시간)
		char *Dt = (char*)dt.c_str();
		int usingtime = atoi(strtok(Dt, ":")) * 60 + atoi(strtok(NULL, ":"));//***지금까지 사용한시간을 분으로 환산

																			 //***유저이름|남은시간-지금까지사용한시간 을 pc클라이언트에 보냄
		if ((*pc)->GetUser()->GetLeftTime() - usingtime >= 0)//***양수면 값 그대로보내고
			snprintf(response, 100, "%s|%d", (*pc)->GetUser()->GetIdentifier().c_str(), (*pc)->GetUser()->GetLeftTime() - usingtime);
		else//***음수면 0을 보냄
			snprintf(response, 100, "%s|%d", (*pc)->GetUser()->GetIdentifier().c_str(), 0);

		send(ClientSocket, response, 100, 0);
		send(ClientSocket, response, 100, 0);
	}
	else if (message[0] == 'm')
	{//***회원가입
		if (DBManager::GetInstance()->Register(message))
		{//***성공
			send(ClientSocket, "1", 99, 0);
			send(ClientSocket, "1", 99, 0);
		}
		else
		{//***실패
			send(ClientSocket, "000", 99, 0);
			send(ClientSocket, "000", 99, 0);
		}
	}
	else if (message[0] == 'l'&&message[1] == 'p')
	{//***유저의 남은시간표시
		strtok(message, "|");
		char*id = strtok(NULL, "|");//***아이디
		char left[10];
		char time[10];
		strcpy(left, DBManager::GetInstance()->ShowTime(id));//***남은시간을 left에 담음
		int l = atoi(strtok(left, ":")) * 60 + atoi(strtok(NULL, ":"));//***남은시간을 분으로 환산
		sprintf(time, "%d", l);//***남은시간을 char*형으로 형변환
		send(ClientSocket, time, 10, 0);
		send(ClientSocket, time, 10, 0);

	}
	else if (message[0] == 's')
	{//***종료
		strtok(message, "|");
		char*t = strtok(NULL, "|");

		char a[6] = { '\0' };
		strcpy(a, (*pc)->GetUser()->GetNowTime());//***처음시작한시간

		std::string dt = Timespan(a, t);//***지금까지사용한시간
		char *Dt = (char*)dt.c_str();
		int usingtime = atoi(strtok(Dt, ":")) * 60 + atoi(strtok(NULL, ":"));//***지금까지 사용한시간 분으로 환산

		DBManager::GetInstance()->Shutdown((char*)((*pc)->GetUser()->GetIdentifier().c_str()), usingtime);//***종료처리
		return false;
	}
	else if (message[0] == 'c')
	{//***비밀번호바꾸기

		if (DBManager::GetInstance()->ChangePassword(message))
		{//***성공
			send(ClientSocket, "1", 99, 0);
			send(ClientSocket, "1", 99, 0);
		}
		else
		{//***실패
			send(ClientSocket, "000", 99, 0);
			send(ClientSocket, "000", 99, 0);
		}
	}
	else if (message[0] == 'f'&&message[1] == 'a')
	{//***비밀번호확인질문
		char question[100];
		char tt[100];
		strcpy(question, DBManager::GetInstance()->Question(message));//확인질문
		sprintf(tt, "%s%s", "****", question);
		send(ClientSocket, " ", 100, 0);
		send(ClientSocket, tt, 100, 0);
	}
	else if (message[0] == 'f'&&message[1] == 'r')
	{//***비밀번호확인질문 정답확인
		if (DBManager::GetInstance()->Answer(message))
		{//***맞
			send(ClientSocket, "1", 99, 0);
			send(ClientSocket, "1", 99, 0);
		}
		else
		{//***틀
			send(ClientSocket, "000", 99, 0);
			send(ClientSocket, "000", 99, 0);
		}

	}
	return true;
}
std::string PCManager::Timespan(char*now, char*end)
{//***시간빼기! 뒤에오는 인자가 무조건 커야한다.

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
