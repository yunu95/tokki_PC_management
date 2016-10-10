#include "User.h"



User::User()
{
	// 사용시간이 만료되었을 때 target_pc에게 강제종료를 요청하는 메서드입니다.
	void AbortUsing(const PC& target_pc)
	{}
	// 사용자의 남은 시간을 설정하는 메서드입니다.
	void SetLeftTime(const float& time)
	{}
}


User::~User()
{
}
