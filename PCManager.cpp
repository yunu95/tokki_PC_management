#include <iostream>
#include <string>
#include <vector>
#include "PCManager.h"
#include "Card.h"
#include "Member.h" // 클래스

PCManager* PCManager::instance = nullptr;; 
PCManager* PCManager::GetInstance() {
	if (instance)
		return instance;
	else
		return instance = new PCManager(); 
}
// 싱글톤 패턴을 구현하는 부분입니다. 

PCManager::PCManager()
{
	commandsList.push_back(std::string("RechargeCard"));
	commandsList.push_back(std::string("RechargeMember"));
	commandsList.push_back(std::string("Checkout"));
	commandsList.push_back(std::string("Status"));
	commandsList.push_back(std::string("Quit"));

	
	cards.push_back(Card::string("1"));
}


PCManager::~PCManager()
{
}
bool PCManager::QueryNextAction() {
	using namespace std;
	cout << "\nCommand List\n";
	for (string each : commandsList) {
		cout << each;
		cout << ",";
	}
	cout << "\n";
	string command;
	getline(cin, command);
	for (string each : commandsList) {
		// 입력된 명령어를 모두 소문자로 바꿔준다.
		for (string::iterator EachChar = command.begin(); EachChar < command.end();EachChar++)
			*EachChar = tolower(*EachChar);

		// 커맨드에 따라 필요한 함수를 호출한다.
		if (command == "rechargecard")
			return true;
		if (command == "rechargemember")
			return true;
		if (command == "checkout")
			return true;
		if (command == "status")
			return true;
		if (command == "quit")
			return false;
	}
	cout << "UnIdentified Command\n";
	return true;
}
void PCManager::Initialize() {
	while (QueryNextAction());
}

void PCManager::RechargeTime(const Card& target, const float& seconds)
	{

		// 손놈 : 카드 번호랑 시간 줄테니까 더해와 
		// 직원 : 네 카드번호가 target번이니까 잠시만요 , cards벡터에서 target번째를 꺼내고 
		//거기에 있는 left_time에 seconds를 더해서 갱신할게요.

	}

void PCManager::RechargeTime(const Member& target, const float& seconds)
	{
		// 멤버 아이디를 요구하고, 아이디 정보를 DB에서 불러옵니다. 
		

		// 정보에 있는 left_time에 seconds를 더해서 갱신합니다.
	}

void PCManager::LoadPCinfos()
{
	//

}
