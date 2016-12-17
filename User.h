#pragma once
#include <string>
#include<ctime>
// 인터페이스 입니다.
class PC; // PC의 상태를 반영해야 하므로 PC 클래스를 넣습니다.
class User
{
private:
protected:
	// 생성자를 protected에 선언해 둔 것은 User는 순수 가상함수만 들어가 있는 클래스이므로
	// 함부로 인스턴스가 만들어지면 안되기 때문입니다.
	User();
	~User();
public:
	// 아래 두 함수는 순수 가상함수입니다.
	// 사용시간이 만료되었을 때 target_pc에게 강제종료를 요청하는 메서드입니다.
	virtual void AbortUsing(const PC& target_pc) = 0;
	// 사용자의 남은 시간을 설정하는 메서드입니다.
	virtual void SetLeftTime(const int& time) = 0;
	virtual std::string GetIdentifier() = 0;
	virtual int GetLeftTime() = 0;
	virtual char* GetNowTime() = 0;
};
