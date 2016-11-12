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
//// Card???°ì´?°ë² ?´ìŠ¤?€ ?°ë™???„ìš”ê°€ ?†ìŠµ?ˆë‹¤.
//class Card :
//	public User
//{
//private:
//	// ì¹´ë“œ???¼ë ¨ë²ˆí˜¸ë¡? ?¤ë¥¸ ì¹´ë“œ?€ ì¤‘ì²©?????†ëŠ” ??ê°???• ???©ë‹ˆ??
//	int card_number;
//	// ë¹„íšŒ???¬ìš©?ì˜ ?¨ì? ?œê°„???œì‹œ?©ë‹ˆ??
//	float left_time;
//public: //
//	Card(const int& _card_number, float& _left_time); // ?ì„±??- ë©¤ë²„ë³€?˜ë? ì´ˆê¸°???©ë‹ˆ??
//	~Card(); // ?Œë©¸??
//};

