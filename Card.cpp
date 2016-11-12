#include "Card.h"
#include "PC.h"

// constructor
Card::Card(const int& _card_number,const float& _left_time) 
{
	card_number = _card_number; 
	left_time = _left_time; 
}


Card::~Card() // destructor
{

}
void Card::AbortUsing(const PC& target) 
{

}
void Card::SetLeftTime(const float& time) 
{
	this->left_time =time;
}
float Card::GetLeftTime() const
{
	//for the clarification, 'this' keyword has been used
	return this->left_time;
}
//#include <iostream>
//
//// Card???�이?�베?�스?� ?�동???�요가 ?�습?�다.
//class Card :
//	public User
//{
//private:
//	// 카드???�련번호�? ?�른 카드?� 중첩?????�는 ??�???��???�니??
//	int card_number;
//	// 비회???�용?�의 ?��? ?�간???�시?�니??
//	float left_time;
//public: //
//	Card(const int& _card_number, float& _left_time); // ?�성??- 멤버변?��? 초기???�니??
//	~Card(); // ?�멸??
//};

