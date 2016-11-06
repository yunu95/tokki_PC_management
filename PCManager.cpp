#include <iostream>
#include <string>
#include <vector>
#include "PCManager.h"
#include "Card.h"
#include "Member.h" // Ŭ����

PCManager* PCManager::instance = nullptr;; 
PCManager* PCManager::GetInstance() {
	if (instance)
		return instance;
	else
		return instance = new PCManager(); 
}
// �̱��� ������ �����ϴ� �κ��Դϴ�. 

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
		// �Էµ� ��ɾ ��� �ҹ��ڷ� �ٲ��ش�.
		for (string::iterator EachChar = command.begin(); EachChar < command.end();EachChar++)
			*EachChar = tolower(*EachChar);

		// Ŀ�ǵ忡 ���� �ʿ��� �Լ��� ȣ���Ѵ�.
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

		// �ճ� : ī�� ��ȣ�� �ð� ���״ϱ� ���ؿ� 
		// ���� : �� ī���ȣ�� target���̴ϱ� ��ø��� , cards���Ϳ��� target��°�� ������ 
		//�ű⿡ �ִ� left_time�� seconds�� ���ؼ� �����ҰԿ�.

	}

void PCManager::RechargeTime(const Member& target, const float& seconds)
	{
		// ��� ���̵� �䱸�ϰ�, ���̵� ������ DB���� �ҷ��ɴϴ�. 
		

		// ������ �ִ� left_time�� seconds�� ���ؼ� �����մϴ�.
	}

void PCManager::LoadPCinfos()
{
	//

}
