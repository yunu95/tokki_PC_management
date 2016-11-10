#pragma once
#include "User.h"

// Card는 데이터베이스와 연동될 필요가 없습니다.
class Card :
	public User
{
private:
	// 카드의 일련번호로, 다른 카드와 중첩될 수 없는 키 값 역할을 합니다.
	int card_number;
	// 비회원 사용자의 남은 시간을 표시합니다.
	float left_time;
public: //
	Card(const int& _card_number, const float& _left_time); // 생성자 - 멤버변수를 초기화 합니다.
	~Card(); // 소멸자

	void AbortUsing(const PC& target);
	void SetLeftTime(const float& time);
	int GetCardNo();
	float GetleftT();
};

