#pragma once
#include <vector>
/*
λͺ¨λ  PC κ°μ²΄?€μ ?Έμ€?΄μ€?€μ ?¬ν¨?κ³  ?λ€. PCλ°©μ μΉ΄μ΄??PC???΄λΉ?λ κ°μ²΄?΄λ€.
*/

// ?λ???΄λ??? μΈ? ?΄λ???λ°©? μΈ?λ??
class Card;
class Member;

class PCManager
{
private:
	PCManager();
	~PCManager();
	static PCManager* instance;
	std::vector<std::string> commandsList;
	// λͺ¨λ  pc?€μ ?Έμ€?΄μ€?€μ? pcs???€μ΄?μ΅?λ€.
	std::vector<class PC*> pcs;
	// λͺ¨λ  Card?€μ ?Έμ€?΄μ€?€μ? cards???€μ΄?μ΅?λ€.
	std::vector<class Card*> cards;
public:
	static PCManager *GetInstance();
	//?λ??? μΈ??RechargeTime λ©μ?λ€λ₯??μ?λ €λ©?method overloading?????μ§?μ΄ ?μ?©λ??
	// λΉν??μΉ΄λ ?΄μ©?μ ?¬μ©?κ°??μΆκ??©λ??
	void RechargeTime( Card& target, const float& seconds);
	// λ‘κ·Έ?Έν???μ?΄μ©?μ ?¬μ©?κ°??μΆκ??©λ??
	void RechargeTime(Member& target, const float& seconds);
	// it initiates every initialization and activate terminal  
	void Initialize();
	bool QueryNextAction();
};
