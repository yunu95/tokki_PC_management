#pragma once
#include "User.h"

// Card???�이?�베?�스?� ?�동???�요가 ?�습?�다.
class Card :
	public User
{
private:
	// 카드???�련번호�? ?�른 카드?� 중첩?????�는 ??�???��???�니??
	int card_number;
	// 비회???�용?�의 ?��? ?�간???�시?�니??
	float left_time;
public:
	// ?�성??- 멤버변?��? 초기???�니??
	Card(const int& _card_number, const float& _left_time = 0.0f);
	// lefttime = 0.0f this means default value of second parameter is 0.0f.
	// you don't have to call constructor specifying both parameters. you only need to specify card_number.
	~Card(); // ?�멸??

	// both declararitions below are overriding User's methods.
	void AbortUsing(const PC& target);
	void SetLeftTime(const float& time);
	float GetLeftTime()const;
};

