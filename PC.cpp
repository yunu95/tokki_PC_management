#include "PC.h"



PC::PC(const int& number)
{
	int PC_Number = number;
	bool is_active = false;
	bool is_power_on = false; 
	current_user = nullptr;
	// 기본적으로 사용자가 없고 꺼져 있는 상태로 초기화 됩니다.
}


PC::~PC()
{
}

//사용자가 컴퓨터를 사용함으로서 사용상태의 멤버 변수인
//is_active 가 true가 된다.
bool PC::StartUsing() {
	is_active = true;
	return true;
}

//사용자가 컴퓨터를 사용을 중지함으로서 사용상태의 멤버 변수인 
//is_active 가 false가 된다.
bool PC::StopUsing() {
	is_active = false;
	return true;
}


bool PC::AbortUsing()
{
	return true; // 수정 필요
}

//사용자가 컴퓨터의 전원을 켬으로서 전원여부의 멤버 변수인 
//is_power_on 가 true가 된다.
bool PC::TurnOnComputer() {
	is_power_on = true;
	return true;
}

//사용자가 컴퓨터의 전원을 끔으로서 전원여부의 멤버 변수인 
//is_power_on 가 false가 된다.
bool PC::TurnOffComputer() {
	is_power_on = false;
	return true;
}


bool PC::GetPower_Status()
{
	return this-> is_power_on;
}

bool PC::Getactive_Status()
{
	return this-> is_active;
}