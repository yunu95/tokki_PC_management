#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "PCManager.h"
#include "Card.h"
#include "Member.h" 
#include "PC.h" 

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

	// 카드 객체를 미리 생성해 cards 벡터 안에 집어넣습니다. 카드의 번호는 1부터 순서대로 생성됩니다.	
	
	for(int i = 0;i < 100 ;i++)
	cards.push_back(new Card(i,0));

	// PC 객체는 이미 생성된 상태겠지요. 100개가 있다고 가정하고 벡터 안에 집어넣습니다.
	for (int i = 0; i < 100; i++)
	pcs.push_back(new PC(i)); 
	
	// Q. PC에도 번호가 있어야 하지 않는지?
	
	// 손님이 멤버인 경우는 데이터 베이스에서 불러오게 됩니다.

	
}
// 여기는 프로그램이 실행되는 공간이 아님. 단지 필드일 뿐

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
			cout << "카드의 일련번호와 추가할 시간을 입력하세요. "<< endl;
			cin >> CardNumber >> PlusTime;
			std::cout << "현재" << cards[CardNumber]->GetCardNo() << "번 카드는" << cards[CardNumber]->GetleftT() << "초인 상태입니다." << std::endl;
			RechargeTime(*cards[CardNumber], PlusTime);
			return true;
		if (command == "rechargemember")
			//RechargeTime(const Member& target, const float& seconds)
			return true;
		if (command == "checkout")
			// 카드를 다시 벡터에 집어넣는다.
			return true;
		if (command == "status")
			// 카드의 정보를 초기화한다. 남은 시간을 0으로 바꾼다.
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

void PCManager::RechargeTime(Card& target, const float& seconds)
	{

		// 손놈 : 카드 번호랑 시간 줄테니까 더해와
		target.SetLeftTime(seconds);
		// 직원 : 네 카드번호가 target번이니까 잠시만요 , cards벡터에서 target번째를 꺼내고
		std::cout << target.GetCardNo() << "번 카드에" << target.GetleftT() << "초가 추가 되었습니다." << std::endl;
		// 거기에 있는 left_time에 seconds를 더해서 갱신할게요.
	}

void PCManager::RechargeTime(const Member& target, const float& seconds)
	{
		// 멤버 아이디를 요구하고, 아이디 정보를 DB에서 불러옵니다.
	

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

/*
Card* PCManager::SearchCard(const int& CardName)
{
	
	// Cards 벡터에서 각 Card.card_number의 값을 탐색하고 맞다면 그 카드 객체를 반환. 

	// iterator를 사용합니다.


	//임시방편.
	return nullptr;
}

*/