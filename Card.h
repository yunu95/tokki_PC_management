#pragma once
#include "User.h"

// Card�� �����ͺ��̽��� ������ �ʿ䰡 �����ϴ�.
class Card :
	public User
{
private:
	// ī���� �Ϸù�ȣ��, �ٸ� ī��� ��ø�� �� ���� Ű �� ������ �մϴ�.
	int card_number;
	// ��ȸ�� ������� ���� �ð��� ǥ���մϴ�.
	float left_time;
public: //
	Card(const int& _card_number, float& _left_time); // ������ - ��������� �ʱ�ȭ �մϴ�.
	~Card(); // �Ҹ���
};

