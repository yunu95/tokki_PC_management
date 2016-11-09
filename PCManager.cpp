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
// �̱��� ������ �����ϴ� �κ��Դϴ�. 

PCManager::PCManager()
{
	commandsList.push_back(std::string("RechargeCard"));
	commandsList.push_back(std::string("RechargeMember"));
	commandsList.push_back(std::string("Checkout"));
	commandsList.push_back(std::string("Status"));
	commandsList.push_back(std::string("Quit")); 

	// �մ��� ī�带 �䱸�ϸ� ī�� ��ü�� ������ �� ���۷����� ���� �ȿ� ����ֽ��ϴ�. ī���� ��ȣ�� 1���� ������� �����˴ϴ�.
	// ī�� ��ü�� (��ȣ,�ð�) �ε� �ð� ��¼��;	
	
	for(int i; ;i++)
	cards.push_back(new Card(1,0));
	// �մ��� PC�� �̿��ϰ� �Ǹ� �� PC ��ü�� ������ �� ���۷����� ���� �ȿ� ����ֽ��ϴ�.
	//pcs.push_back();
	// �մ��� ����� ���� ������ ���̽����� �ҷ����� �˴ϴ�.
	// ���⼭ �� ��ü�� �����ؾߵǴµ� ��� ����? �׸��� �Լ��� ������ �ϳ�?
	// ��� ���Ϳ� �������?
	
}
// ����� ���α׷��� ����Ǵ� ������ �ƴ�. ���� �ʵ��� ��
Card c1(0, 0.0f);

Card c2(0, 0.0f);
Card c3(0, 0.0f);
//�ݺ���.. �̷������� �� �� ����� �ΰ�, ���Ϳ� ����ֽ��ϴ�. ī���� �⺻���� 100���� �ϰڽ��ϴ�.

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
			cout << "�߰��� �ð��� �Ϸù�ȣ�� �Է��ϼ���. "<< endl;
			cin >> PlusTime >> CardNumber;
			//RechargeTime(SearchCard(CardNumber), PlusTime);
			return true;
		if (command == "rechargemember")
			//RechargeTime(const Member& target, const float& seconds)
			return true;
		if (command == "checkout")
			// ī�带 �ٽ� ���Ϳ� ����ִ´�.
			return true;
		if (command == "status")
			// ī���� ������ �ʱ�ȭ�Ѵ�. ���� �ð��� 0���� �ٲ۴�.
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
		// �ű⿡ �ִ� left_time�� seconds�� ���ؼ� �����ҰԿ�.

	}

void PCManager::RechargeTime(const Member& target, const float& seconds)
	{
		// ��� ���̵� �䱸�ϰ�, ���̵� ������ DB���� �ҷ��ɴϴ�.
		

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

Card* PCManager::SearchCard(const int& CardName)
{
	
	// Cards ���Ϳ��� �� Card.card_number�� ���� Ž���ϰ� �´ٸ� �� ī�� ��ü�� ��ȯ. 

	// iterator�� ����մϴ�.

	//retrun card_object;

	//�ӽù���.
	return nullptr;
}

