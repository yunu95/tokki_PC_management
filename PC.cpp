#include "PC.h"



PC::PC()
{
}


PC::~PC()
{
}


bool PC::StartUsing() {
	is_active = true;
	return true;
}
//startusing 메소드 내부에서 
//DB매니저의 레지스터나 로그인 메소드 호출됨
//사용자가 컴퓨터를 사용함으로서 사용상태의 멤버 변수인
//is_active 가 true가 된다.

bool PC::StopUsing() {
	is_active = false;
	return true;
}
//사용자가 컴퓨터를 사용을 중지으로서 사용상태의 멤버 변수인 
//is_active 가 false가 된다.

bool PC::TurnOnComputer() {
	is_power_on = true;
	return true;
}
//사용자가 컴퓨터의 전원을 켬으로서 전원여부의 멤버 변수인 
//is_power_on 가 true가 된다.

bool PC::TurnOffComputer() {
	is_power_on = false;
	return true;
}
//사용자가 컴퓨터의 전원을 끔으로서 전원여부의 멤버 변수인 
//is_power_on 가 false가 된다.
//code by Vincent
