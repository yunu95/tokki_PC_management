#pragma once
#include "User.h"

// Card???°ì´?°ë² ?´ìŠ¤?€ ?°ë™???„ìš”ê°€ ?†ìŠµ?ˆë‹¤.
class Card :
	public User
{
private:
	// ì¹´ë“œ???¼ë ¨ë²ˆí˜¸ë¡? ?¤ë¥¸ ì¹´ë“œ?€ ì¤‘ì²©?????†ëŠ” ??ê°???• ???©ë‹ˆ??
	int card_number;
	// ë¹„íšŒ???¬ìš©?ì˜ ?¨ì? ?œê°„???œì‹œ?©ë‹ˆ??
	float left_time;
public:
	// ?ì„±??- ë©¤ë²„ë³€?˜ë? ì´ˆê¸°???©ë‹ˆ??
	Card(const int& _card_number, const float& _left_time = 0.0f);
	// lefttime = 0.0f this means default value of second parameter is 0.0f.
	// you don't have to call constructor specifying both parameters. you only need to specify card_number.
	~Card(); // ?Œë©¸??

	// both declararitions below are overriding User's methods.
	void AbortUsing(const PC& target);
	void SetLeftTime(const float& time);
	float GetLeftTime()const;
};

