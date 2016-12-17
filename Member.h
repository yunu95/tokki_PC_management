#pragma once
#include <string>
#include "User.h"
/*
회원가입해서 아이디랑 비번이 모두 다 있는 User를 표현합니다.
db에 있는 튜플의 정보를 그대로 클라이언트 객체로 대응시키기 위한 클래스입니다.
*/
class PC;
class Member :
	public User
{
private:
	// 사용자에게 남은 시간입니다.
	int left_time;
	std::string id;
	std::string nowtime;
public:
	// 튜플의 정보를 그대로 받으면 됩니다.
	Member(std::string id, std::string nowtime);
	~Member();
	// 시간이 다 되었을 때 발동되는 메서드입니다. target PC에게 강제종료를 요청하고,
	// DB에서 남은 시간을 차감하는 것 또한 요청해야 합니다.
	virtual void AbortUsing(const PC& target) override;
	virtual void SetLeftTime(const int& time) override;
	virtual std::string GetIdentifier() override;
	virtual int GetLeftTime() override;
	virtual char* GetNowTime() override;
};

