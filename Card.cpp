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
//// Card???°μ΄?°λ² ?΄μ€? ?°λ???μκ° ?μ΅?λ€.
//class Card :
//	public User
//{
//private:
//	// μΉ΄λ???Όλ ¨λ²νΈλ‘? ?€λ₯Έ μΉ΄λ? μ€μ²©?????λ ??κ°??? ???©λ??
//	int card_number;
//	// λΉν???¬μ©?μ ?¨μ? ?κ°???μ?©λ??
//	float left_time;
//public: //
//	Card(const int& _card_number, float& _left_time); // ?μ±??- λ©€λ²λ³?λ? μ΄κΈ°???©λ??
//	~Card(); // ?λ©Έ??
//};

