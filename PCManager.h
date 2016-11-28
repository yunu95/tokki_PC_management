#pragma once
#include <vector>
#include <thread> // 스레드는 한개만 만들면 됨.
#include <stdio.h>
#include <WinSock2.h>
#include <process.h>
/*
모든 PC 객체들의 인스턴스들을 포함하고 있다. PC방의 카운터 PC에 해당되는 객체이다. - 싱글톤 패턴 적용.
*/

// 아래의 클래스 선언은 클래스 전방선언입니다.
class Card;
class Member;
class PC;

class PCManager
{
private:
	PCManager();
	~PCManager();
	// It waits for the message from pc clients.
	void KeepAccepting();
	// 싱글톤 패턴이기 때문에, 클래스 외부에서 함부로 객체를 만들면 안 됩니다. 따라서 생성자는 private로 선언됩니다. 
	static PCManager* instance; // 이 클래스의 유일한 객체를 가리키는 포인터입니다.
	std::vector<std::string> commandsList;
	// 모든 pc들의 인스턴스들은 pcs에 들어있습니다.
	std::vector<class PC*> pcs;
	// 모든 Card들의 인스턴스들은 cards에 들어있습니다.
	std::vector<class Card*> cards;
	WSADATA wsaData;
	SOCKET serv_sock;
	SOCKADDR_IN serv_addr = { 0 };               // 초기화
	std::vector<SOCKET> clnt_socks;
	//pc들의 현 상태를 매 초마다 시간에 맞게 업데이트 시켜주는 스레드입니다.
	std::thread pcs_updater_thread;
	// accept 스레드는 pc가 매니저에 접속하는 것을 대기하면서, pc가 접속하면 연결을 만들어주는 스레드
	std::thread accept_thread;
	// ReceiveThreads에 들어간 스레드들은 한번 pc와 연결이 되면 그 pc들로부터 어떤 연락이 올지 계속 대기하는 스레드
	std::vector<std::thread> RecieveThreads;
	float PlusTime;
	int CardNumber;
public:
	std::thread Updater; // 매 초마다 LoadPCinfos()를 호출하고, 각 PC들의 상태를 업데이트하는 thread
	static PCManager *GetInstance(); // 정적 메서드로서, 클래스의 객체를 만들 때 사용합니다.
									 //아래에 선언된 RechargeTime 메서드들를 정의하려면 method overloading에 대한 지식이 필요합니다.
									 // 비회원 카드 이용자의 사용시간을 추가합니다.
	void RechargeTime(Card& target, const float& seconds);
	// 로그인하는 회원이용자의 사용시간을 추가합니다.
	void RechargeTime(const Member& target, const float& seconds);
	// it initiates every initialization and activate terminal  
	void Initialize();
	bool QueryNextAction(); // 사용자에게 명령어를 요구하고, 입력된 명령어에 대응하는 메서드를 실행합니다.
	void LoadPCinfos(); // PC방에 있는 PC들의 정보를 파일에서 읽어 옵니다.
	void CheckoutCard(Card& card); // 카드를 초기화합니다. 정보는 시간뿐이니 시간을 0으로 만듭니다.
};