#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "PCManager.h"
#include "PCManager.h"
#include "Card.h"
#include "Member.h" 
#include "PC.h"

// these somesome codes below contain everything needed for singletone desgin pattern
// this class pointer is the only instance of this class
PCManager* PCManager::instance = nullptr;; 

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
	} // commandsList 출력

	cout << "\n";
	string command;
	getline(cin, command);
	for (string each : commandsList) {
		// 입력된 명령어를 모두 소문자로 바꿔준다.
		for (string::iterator EachChar = command.begin(); EachChar < command.end();EachChar++)
			*EachChar = tolower(*EachChar);

		// 커맨드에 따라 필요한 함수를 호출한다.
		if (command == "rechargecard") {

			cout << "카드의 일련번호와 추가할 시간을 입력하세요. " << endl;
			cin >> CardNumber >> PlusTime;

			cout << "현재" << cards[CardNumber]->GetCardNo() << "번 카드는"
				<< cards[CardNumber]->GetLeftTime() << "초인 상태입니다." << endl;
			RechargeTime(*cards[CardNumber], PlusTime);

			CardNumber = NULL;
			PlusTime = 0.0;

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			return true;
		}
		if (command == "rechargemember") {
			//RechargeTime(const Member& target, const float& seconds)
			return true;
		}
		if (command == "checkout") {
			// checkout - Do initialize information this card.
			cout << "카드의 일련번호를 입력하세요. " << endl;
			cin >> CardNumber;
			CheckoutCard(*cards[CardNumber]);
			cout << cards[CardNumber]->GetCardNo() << "번 카드가 "
				<< cards[CardNumber]->GetLeftTime() << "초로 초기화 되었습니다." << endl;
			
			CardNumber = NULL;

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			return true;
		}
		if (command == "status") {
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
			
			cout << "현재 켜져 있는 PC의 대수는 " << On_count << " 대 입니다." <<endl;
			cout << "현재 꺼져 있는 PC의 대수는 " << OFF_count << " 대 입니다." << endl;
			cout << "현재 사용되고 있는 PC의 대수는 " << active_count << " 대 입니다." << endl;

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

		// 손놈 : 카드 번호랑 시간 줄테니까 더해와
		target.PlusLeftTime(seconds);
		// 직원 : 네 카드번호가 target번이니까 잠시만요 , cards벡터에서 target번째를 꺼내고
		std::cout << target.GetCardNo() << "번 카드에" 
			<< seconds << "초가 추가 되었습니다." << std::endl;
		// 거기에 있는 left_time에 seconds를 더해서 갱신할게요.
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

void PCManager::CheckoutCard(Card& card)
{
	card.SetLeftTime(0);
}