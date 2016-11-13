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
	
	for(int i = 0;i < 100 ;i++)
	cards.push_back(new Card(i,0));

	// PC ��ü�� �̹� ������ ���°�����. 100���� �ִٰ� �����ϰ� ���� �ȿ� ����ֽ��ϴ�.
	for (int i = 0; i < 100; i++)
	pcs.push_back(new PC(i)); 
	
	// �մ��� ����� ���� ������ ���̽����� �ҷ����� �˴ϴ�.

	
}
// ����� ���α׷��� ����Ǵ� ������ �ƴ�. ���� �ʵ��� ��

PCManager::~PCManager()
{
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
	for (string each : commandsList) {
		// �Էµ� ��ɾ ��� �ҹ��ڷ� �ٲ��ش�.
		for (string::iterator EachChar = command.begin(); EachChar < command.end();EachChar++)
			*EachChar = tolower(*EachChar);

		// Ŀ�ǵ忡 ���� �ʿ��� �Լ��� ȣ���Ѵ�. - ��, �ð��� �߰��� �� �ֵ��� �Ѵ�.
		if (command == "rechargecard") {

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
			return true;
		}
		if (command == "checkout") {
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
		if (command == "status") {
				//PC ����Ȯ���� ���� PC���� pc�� �� �� �밡 ���� �ְ� ��밡 ���� �ִ���, -  is_power_on
				//�� �� �밡 ��������� pc���� ���¸� �����ش�. - is_active
				// ���ͷ����ͷ� ���Ϳ��� �� �� ���� �� ������ �����մϴ�.
			
			cout << "�� PC�� ��� :";
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
			
			cout << "���� ���� �ִ� PC�� ����� " << On_count << " �� �Դϴ�." <<endl;
			cout << "���� ���� �ִ� PC�� ����� " << OFF_count << " �� �Դϴ�." << endl;
			cout << "���� ���ǰ� �ִ� PC�� ����� " << active_count << " �� �Դϴ�." << endl;
			cout << "�ܿ� �¼� : " << active_count << "/";
			LoadPCinfos();
			
		
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
		cout << inputString << endl;
	}
	inputFile.close();
}

void PCManager::CheckoutCard(Card& card)
{
	card.SetLeftTime(0);
}