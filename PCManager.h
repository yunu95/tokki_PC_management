#pragma once
#include <vector>
#include <thread> // ������� �Ѱ��� ����� ��.

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
	// �̱��� �����̱� ������, Ŭ���� �ܺο��� �Ժη� ��ü�� ����� �� �˴ϴ�. ���� �����ڴ� private�� ����˴ϴ�. 
	static PCManager* instance; // �� Ŭ������ ������ ��ü�� ����Ű�� �������Դϴ�.
	std::vector<std::string> commandsList;
	// ��� pc���� �ν��Ͻ����� pcs�� ����ֽ��ϴ�.
	std::vector<class PC*> pcs;
	// ��� Card���� �ν��Ͻ����� cards�� ����ֽ��ϴ�.
	std::vector<class Card*> cards;
	
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

/* *** �߰���� ****

1. ������
2. �����¼� �����ִ� ��(53 / 100) �̷���
3. ���� ��Ű�°�
4. �ڸ� �ű�°�
5. ä��
6. ����
7. �̸��� �ߺ��� ȸ������ �Ұ�
8. ��й�ȣ ã��

*/