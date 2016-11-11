#include "PC.h"



PC::PC(const int& number)
{
	int PC_Number = number;
	bool is_active = false;
	bool is_power_on = false; 
	class User* current_user = nullptr;
	// �⺻������ ����ڰ� ���� ���� �ִ� ���·� �ʱ�ȭ �˴ϴ�.
}


PC::~PC()
{
}


bool PC::StartUsing() {
	is_active = true;
	return true;
}
//����ڰ� ��ǻ�͸� ��������μ� �������� ��� ������
//is_active �� true�� �ȴ�.

bool PC::StopUsing() {
	is_active = false;
	return true;
}
//����ڰ� ��ǻ�͸� ����� ���������μ� �������� ��� ������ 
//is_active �� false�� �ȴ�.

bool PC::AbortUsing()
{
	return true; // ���� �ʿ�
}

bool PC::TurnOnComputer() {
	is_power_on = true;
	return true;
}
//����ڰ� ��ǻ���� ������ �����μ� ���������� ��� ������ 
//is_power_on �� true�� �ȴ�.

bool PC::TurnOffComputer() {
	is_power_on = false;
	return true;
}
//����ڰ� ��ǻ���� ������ �����μ� ���������� ��� ������ 
//is_power_on �� false�� �ȴ�.
//code by Vincent