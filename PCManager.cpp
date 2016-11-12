#include <iostream>
#include <string>
#include <vector>
#include "PCManager.h"
#include "DBManager.h"
#include "Card.h"
#include "Member.h"

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

// initiates all the commands needed in terminal.
PCManager::PCManager()
{
	cards.push_back(new Card(0));
	commandsList.push_back(std::string("RechargeCard"));
	commandsList.push_back(std::string("RechargeMember"));
	commandsList.push_back(std::string("Checkout"));
	commandsList.push_back(std::string("Status"));
	commandsList.push_back(std::string("Quit"));
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
	for (string each : commandsList) 
	{
		// ?…ë ¥??ëª…ë ¹?´ë? ëª¨ë‘ ?Œë¬¸?ë¡œ ë°”ê¿”ì¤€??
		for (string::iterator EachChar = command.begin(); EachChar < command.end(); EachChar++)
			*EachChar = tolower(*EachChar);

		// ì»¤ë§¨?œì— ?°ë¼ ?„ìš”???¨ìˆ˜ë¥??¸ì¶œ?œë‹¤.
		if (command == "rechargecard")
		{
			int card_num;
			float time;
			cin >> card_num;
			cin >> time;
			RechargeTime(*cards[card_num],time);
			return true;
		}
		if (command == "rechargemember") 
		{
			string id;
			float time;
			cin >> id;
			cin >> time;
			RechargeTime(*DBManager::GetInstance()->GetMemberinfo(id), time);
			return true;
		}
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
void PCManager::Initialize() 
{
	while (QueryNextAction());
}

void::PCManager::RechargeTime(Card& target, const float& seconds) 
{
	target.SetLeftTime(target.GetLeftTime() + seconds);
}
void::PCManager::RechargeTime(Member& target, const float& seconds) 
{
	// below here should be placed socket programming things
	// which means, Back to work! sung yeon!
}
