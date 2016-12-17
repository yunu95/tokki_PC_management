#include "PC.h"
#include "User.h"
#include <iostream>


PC::PC(const int& number)
{
	this->PC_Number = number;
	this->is_active = false;
	this->is_power_on = false;
	current_user = nullptr;
	// 기본적으로 사용자가 없고 꺼져 있는 상태로 초기화 됩니다.
}


PC::~PC()
{
}


bool PC::StartUsing(User* user)
{

	this->current_user = user;
	is_active = true;
	std::cout << "\
PC " << PC_Number << "has started!\n\
current User : " << current_user->GetIdentifier().c_str() << "\n";
	return true;
}
//사용자가 컴퓨터를 사용함으로서 사용상태의 멤버 변수인
//is_active 가 true가 된다.

bool PC::StopUsing() {
	is_active = false;
	return true;
}
//사용자가 컴퓨터를 사용을 중지함으로서 사용상태의 멤버 변수인 
//is_active 가 false가 된다.

bool PC::AbortUsing()
{
	return true;
}

bool PC::TurnOnComputer() {
	std::cout << "\nPC " << PC_Number << " Has been turned on!";
	is_power_on = true;
	is_active = true;
	return true;
}
//사용자가 컴퓨터의 전원을 켬으로서 전원여부의 멤버 변수인 
//is_power_on 가 true가 된다.

bool PC::TurnOffComputer()
{//***컴퓨터끌때 변수들다 false로 바꿈
	std::cout << "\nPC " << PC_Number << " Has been turned off!" << std::endl;
	is_power_on = false;
	is_active = false;
	return true;
}

//사용자가 컴퓨터의 전원을 끔으로서 전원여부의 멤버 변수인 
//is_power_on 가 false가 된다.
//code by Vincent

bool PC::GetPower_Status()
{
	return this->is_power_on;
}
bool PC::Getactive_Status()
{
	return this->is_active;
}

User * PC::GetUser()
{
	return current_user;
}
