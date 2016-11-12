#pragma once
#include "User.h"

// Card???°μ΄?°λ² ?΄μ€? ?°λ???μκ° ?μ΅?λ€.
class Card :
	public User
{
private:
	// μΉ΄λ???Όλ ¨λ²νΈλ‘? ?€λ₯Έ μΉ΄λ? μ€μ²©?????λ ??κ°??? ???©λ??
	int card_number;
	// λΉν???¬μ©?μ ?¨μ? ?κ°???μ?©λ??
	float left_time;
public:
	// ?μ±??- λ©€λ²λ³?λ? μ΄κΈ°???©λ??
	Card(const int& _card_number, const float& _left_time = 0.0f);
	// lefttime = 0.0f this means default value of second parameter is 0.0f.
	// you don't have to call constructor specifying both parameters. you only need to specify card_number.
	~Card(); // ?λ©Έ??

	// both declararitions below are overriding User's methods.
	void AbortUsing(const PC& target);
	void SetLeftTime(const float& time);
	float GetLeftTime()const;
};

