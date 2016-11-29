#include "PC.h"
#include "User.h"
#include <iostream>


PC::PC(const int& number)
{
	this->PC_Number = number;
	this->is_active = false;
	this->is_power_on = false;
	current_user = nullptr;
	// �⺻������ ����ڰ� ���� ���� �ִ� ���·� �ʱ�ȭ �˴ϴ�.
}


PC::~PC()
{
}


bool PC::StartUsing(User* user)
{

	this->current_user = user;
	is_active = true;
		std::cout <<"\
PC " << PC_Number << "has started!\n\
current User : " << current_user->GetIdentifier().c_str() << "\n";
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
	std::cout << "\nPC " << PC_Number << " Has been turned on!";
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

bool PC::GetPower_Status()
{
	return this->is_power_on;
}
bool PC::Getactive_Status()
{
	return this->is_active;
}