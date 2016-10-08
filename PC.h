#pragma once
/*
PC방에서 관리되는 PC 하나의 상태를 표현하기 위해 만들어진 클래스입니다.
*/


class PC
{
private:
	// 컴퓨터의 사용여부를 표시합니다.
	bool is_active;
	// 컴퓨터 전원이 켜져 있는지의 여부를 표시합니다.
	bool is_power_on;
	// 현재 사용자를 뜻합니다.
	class User* current_user;
public:
	PC();
	~PC();
	// User가 해당 PC 사용을 시작합니다.
	bool StartUsing();
	// USer가 해당 PC 사용을 중지합니다.
	bool StopUsing();
	// User가 시간이 다 만료되어 사용이 중단됩니다. 이 메서드는 User에게서 호출됩니다.
	bool AbortUsing();
	// 컴퓨터 전원을 킵니다.
	bool TurnOnComputer();
	// 전원을 끕니다.
	bool TurnOffComputer();
};

