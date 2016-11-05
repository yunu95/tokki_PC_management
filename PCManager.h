#pragma once
#include <vector>
/*
��� PC ��ü���� �ν��Ͻ����� �����ϰ� �ִ�. PC���� ī���� PC�� �ش�Ǵ� ��ü�̴�.
*/
class PCManager
{
private:
	PCManager();
	~PCManager();
	static PCManager* instance;
	std::vector<std::string> commandsList;
	// ��� pc���� �ν��Ͻ����� pcs�� ����ֽ��ϴ�.
	std::vector<class PC*> pcs;
	// ��� Card���� �ν��Ͻ����� cards�� ����ֽ��ϴ�.
	std::vector<class Card*> cards;
public:
	// �Ʒ��� Ŭ���� ������ Ŭ���� ���漱���Դϴ�.
	class Card;
	class Member;
	static PCManager *GetInstance();
	//�Ʒ��� ����� RechargeTime �޼���鸦 �����Ϸ��� method overloading�� ���� ������ �ʿ��մϴ�.
	// ��ȸ�� ī�� �̿����� ���ð��� �߰��մϴ�.
	void RechargeTime(const Card& target, const float& seconds);
	// �α����ϴ� ȸ���̿����� ���ð��� �߰��մϴ�.
	void RechargeTime(const Member& target, const float& seconds);
	// it initiates every initialization and activate terminal  
	void Initialize();
	bool QueryNextAction();
};