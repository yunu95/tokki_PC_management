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

	// 손님이 카드를 요구하면 카드 객체를 생성해 그 레퍼런스를 벡터 안에 집어넣습니다. 카드의 번호는 1부터 순서대로 생성됩니다.
	// 카드 객체는 (번호,시간) 인데 시간 어쩌냐;	
	
	cards.push_back(new Card(1,0));
	// 손님이 PC를 이용하게 되면 그 PC 객체를 생성해 그 레퍼런스를 벡터 안에 집어넣습니다.
	//pcs.push_back();
	// 손님이 멤버인 경우는 데이터 베이스에서 불러오게 됩니다.
	// 여기서 각 객체를 생성해야되는데 어떻게 하지? 그리고 함수를 만들어야 하나?
	// 어떻게 벡터에 집어넣지?
	
}
// 여기는 프로그램이 실행되는 공간이 아님. 단지 필드일 뿐
Card c1(0, 0.0f);

Card c2(0, 0.0f);
Card c3(0, 0.0f);
//반복문.. 이런식으로 싹 다 만들어 두고, 벡터에 집어넣습니다. 카드의 기본값은 100으로 하겠습니다.

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
			cout << "추가할 시간과 일련번호를 입력하세요. "<< endl;
			cin >> PlusTime >> CardNumber;
			//RechargeTime(SearchCard(CardNumber), PlusTime);
			return true;
		if (command == "rechargemember")
			//RechargeTime(const Member& target, const float& seconds)
			return true;
		if (command == "checkout")
			return true;
		if (command == "status")
			// 
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

Card* PCManager::SearchCard(const int& CardName)
{
	
	// Cards 벡터에서 각 Card.card_number의 값을 탐색하고 맞다면 그 카드 객체를 반환. 

	// iterator를 사용합니다.

	//retrun card_object;

	//임시방편.
	return nullptr;
}

