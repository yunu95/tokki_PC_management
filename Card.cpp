#include "Card.h"

Card::Card(const int& _card_number,const float& _left_time) // constructor
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
	left_time = left_time + time;
}

int Card::GetCardNo()
{
	return this->card_number;
}
float Card::GetleftT()
{
	return this->left_time;
}
