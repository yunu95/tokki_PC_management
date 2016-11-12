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
public: 
	// ������ - ��������� �ʱ�ȭ �մϴ�.
	Card(const int& _card_number, const float& _left_time = 0.0f);
	// lefttime = 0.0f this means default value of second parameter is 0.0f.
	// you don't have to call constructor specifying both parameters. you only need to specify card_number.
	~Card(); // �Ҹ���

	// both declararitions below are overriding User's methods.
	void AbortUsing(const PC& target);
	void SetLeftTime(const float& time);
	int GetCardNo();
	float GetLeftTime()const;
	void PlusLeftTime(const float& time);
};

