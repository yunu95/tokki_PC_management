#pragma once
#include "User.h"
class Card :
	public User
{
private:
	// ī���� �Ϸù�ȣ��, �ٸ� ī��� ��ø�� �� ���� Ű �� ������ �մϴ�.
	int card_number;
	// ��ȸ�� ������� ���� �ð��� ǥ���մϴ�.
	float left_time;
public:
	Card();
	~Card();
};
