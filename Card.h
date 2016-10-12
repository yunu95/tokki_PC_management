#pragma once
#include "User.h"
class Card :
	public User
{
private:
	// 카드의 일련번호로, 다른 카드와 중첩될 수 없는 키 값 역할을 합니다.
	int card_number;
	// 비회원 사용자의 남은 시간을 표시합니다.
	float left_time;
public: //
	Card();
	~Card();
};

