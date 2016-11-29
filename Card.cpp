#include "Card.h"

Card::Card(const int& _card_number, const float& _left_time) // constructor
{
	card_number = _card_number;
	left_time = _left_time;
}


Card::~Card() // destructor
{

}

void Card::AbortUsing(const PC& target) {

}

void Card::SetLeftTime(const float& time) {
	this->left_time = time;
}
// Q. this->left_time = time; 둘 중 어느 것이 원하는 것인가?

int Card::GetCardNo()
{
	return this->card_number;
}
float Card::GetLeftTime() const
{
	//for the clarification, 'this' keyword has been used
	return this->left_time;
}

void Card::PlusLeftTime(const float& time) {
	this->left_time = left_time + time;
}

std::string Card::GetIdentifier()
{
	return std::string("card " + card_number);
}
