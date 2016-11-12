#pragma once
#include <vector>
/*
ëª¨ë“  PC ê°ì²´?¤ì˜ ?¸ìŠ¤?´ìŠ¤?¤ì„ ?¬í•¨?˜ê³  ?ˆë‹¤. PCë°©ì˜ ì¹´ìš´??PC???´ë‹¹?˜ëŠ” ê°ì²´?´ë‹¤.
*/

// ?„ë˜???´ë˜??? ì–¸?€ ?´ë˜???„ë°©? ì–¸?…ë‹ˆ??
class Card;
class Member;

class PCManager
{
private:
	PCManager();
	~PCManager();
	static PCManager* instance;
	std::vector<std::string> commandsList;
	// ëª¨ë“  pc?¤ì˜ ?¸ìŠ¤?´ìŠ¤?¤ì? pcs???¤ì–´?ˆìŠµ?ˆë‹¤.
	std::vector<class PC*> pcs;
	// ëª¨ë“  Card?¤ì˜ ?¸ìŠ¤?´ìŠ¤?¤ì? cards???¤ì–´?ˆìŠµ?ˆë‹¤.
	std::vector<class Card*> cards;
public:
	static PCManager *GetInstance();
	//?„ë˜??? ì–¸??RechargeTime ë©”ì„œ?œë“¤ë¥??•ì˜?˜ë ¤ë©?method overloading???€??ì§€?ì´ ?„ìš”?©ë‹ˆ??
	// ë¹„íšŒ??ì¹´ë“œ ?´ìš©?ì˜ ?¬ìš©?œê°„??ì¶”ê??©ë‹ˆ??
	void RechargeTime( Card& target, const float& seconds);
	// ë¡œê·¸?¸í•˜???Œì›?´ìš©?ì˜ ?¬ìš©?œê°„??ì¶”ê??©ë‹ˆ??
	void RechargeTime(Member& target, const float& seconds);
	// it initiates every initialization and activate terminal  
	void Initialize();
	bool QueryNextAction();
};
