#pragma once
#include <vector>
#include <thread> // 스레드는 한개만 만들면 됨.

/*
모든 PC 객체들의 인스턴스들을 포함하고 있다. PC방의 카운터 PC에 해당되는 객체이다. - 싱글톤 패턴 적용.
*/

// 아래의 클래스 선언은 클래스 전방선언입니다.
class Card;
class Member;
class PC;

class PCManager
{
private:
	PCManager();
	~PCManager(); 
	// 싱글톤 패턴이기 때문에, 클래스 외부에서 함부로 객체를 만들면 안 됩니다. 따라서 생성자는 private로 선언됩니다. 
	static PCManager* instance; // 이 클래스의 유일한 객체를 가리키는 포인터입니다.
	std::vector<std::string> commandsList;
	// 모든 pc들의 인스턴스들은 pcs에 들어있습니다.
	std::vector<class PC*> pcs;
	// 모든 Card들의 인스턴스들은 cards에 들어있습니다.
	std::vector<class Card*> cards;
	
	float PlusTime;
	int CardNumber;
public:
	std::thread Updater; // 매 초마다 LoadPCinfos()를 호출하고, 각 PC들의 상태를 업데이트하는 thread
	static PCManager *GetInstance(); // 정적 메서드로서, 클래스의 객체를 만들 때 사용합니다.
	//아래에 선언된 RechargeTime 메서드들를 정의하려면 method overloading에 대한 지식이 필요합니다.
	// 비회원 카드 이용자의 사용시간을 추가합니다.
	void RechargeTime(Card& target, const float& seconds);
	// 로그인하는 회원이용자의 사용시간을 추가합니다.
	void RechargeTime(const Member& target, const float& seconds);
	// it initiates every initialization and activate terminal  
	void Initialize();
	bool QueryNextAction(); // 사용자에게 명령어를 요구하고, 입력된 명령어에 대응하는 메서드를 실행합니다.
	void LoadPCinfos(); // PC방에 있는 PC들의 정보를 파일에서 읽어 옵니다.
	void CheckoutCard(Card& card); // 카드를 초기화합니다. 정보는 시간뿐이니 시간을 0으로 만듭니다.
};