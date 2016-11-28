#pragma once
#include <vector>
#include <thread> // ������� �Ѱ��� ����� ��.
#include <stdio.h>
#include <WinSock2.h>
#include <process.h>
/*
��� PC ��ü���� �ν��Ͻ����� �����ϰ� �ִ�. PC���� ī���� PC�� �ش�Ǵ� ��ü�̴�. - �̱��� ���� ����.
*/

// �Ʒ��� Ŭ���� ������ Ŭ���� ���漱���Դϴ�.
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
	// �̱��� �����̱� ������, Ŭ���� �ܺο��� �Ժη� ��ü�� ����� �� �˴ϴ�. ���� �����ڴ� private�� ����˴ϴ�. 
	static PCManager* instance; // �� Ŭ������ ������ ��ü�� ����Ű�� �������Դϴ�.
	std::vector<std::string> commandsList;
	// ��� pc���� �ν��Ͻ����� pcs�� ����ֽ��ϴ�.
	std::vector<class PC*> pcs;
	// ��� Card���� �ν��Ͻ����� cards�� ����ֽ��ϴ�.
	std::vector<class Card*> cards;
	WSADATA wsaData;
	SOCKET serv_sock;
	SOCKADDR_IN serv_addr = { 0 };               // �ʱ�ȭ
	std::vector<SOCKET> clnt_socks;
	//pc���� �� ���¸� �� �ʸ��� �ð��� �°� ������Ʈ �����ִ� �������Դϴ�.
	std::thread pcs_updater_thread;
	// accept ������� pc�� �Ŵ����� �����ϴ� ���� ����ϸ鼭, pc�� �����ϸ� ������ ������ִ� ������
	std::thread accept_thread;
	// ReceiveThreads�� �� ��������� �ѹ� pc�� ������ �Ǹ� �� pc��κ��� � ������ ���� ��� ����ϴ� ������
	std::vector<std::thread> RecieveThreads;
	float PlusTime;
	int CardNumber;
public:
	std::thread Updater; // �� �ʸ��� LoadPCinfos()�� ȣ���ϰ�, �� PC���� ���¸� ������Ʈ�ϴ� thread
	static PCManager *GetInstance(); // ���� �޼���μ�, Ŭ������ ��ü�� ���� �� ����մϴ�.
									 //�Ʒ��� ����� RechargeTime �޼���鸦 �����Ϸ��� method overloading�� ���� ������ �ʿ��մϴ�.
									 // ��ȸ�� ī�� �̿����� ���ð��� �߰��մϴ�.
	void RechargeTime(Card& target, const float& seconds);
	// �α����ϴ� ȸ���̿����� ���ð��� �߰��մϴ�.
	void RechargeTime(const Member& target, const float& seconds);
	// it initiates every initialization and activate terminal  
	void Initialize();
	bool QueryNextAction(); // ����ڿ��� ��ɾ �䱸�ϰ�, �Էµ� ��ɾ �����ϴ� �޼��带 �����մϴ�.
	void LoadPCinfos(); // PC�濡 �ִ� PC���� ������ ���Ͽ��� �о� �ɴϴ�.
	void CheckoutCard(Card& card); // ī�带 �ʱ�ȭ�մϴ�. ������ �ð����̴� �ð��� 0���� ����ϴ�.
};