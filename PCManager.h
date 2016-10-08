#pragma once
#include <vector>
/*
모든 PC 객체들의 인스턴스들을 포함하고 있다. PC방의 카운터 PC에 해당되는 객체이다.
*/
class PCManager
{
private:
	PCManager();
	~PCManager();
	static PCManager* instance;
	// 모든 pc들의 인스턴스들은 pcs에 들어있습니다.
	std::vector<class PC*> pcs;
	// 모든 Card들의 인스턴스들은 cards에 들어있습니다.
	std::vector<class Card*> cards;
public:
	// 아래의 클래스 선언은 클래스 전방선언입니다.
	class Card;
	class Member;
	static PCManager *GetInstance();
	//아래에 선언된 RechargeTime 메서드들를 정의하려면 method overloading에 대한 지식이 필요합니다.
	// 비회원 카드 이용자의 사용시간을 추가합니다.
	void RechargeTime(const Card& target, const float& seconds);
	// 로그인하는 회원이용자의 사용시간을 추가합니다.
	void RechargeTime(const Member& target, const float& seconds);

};