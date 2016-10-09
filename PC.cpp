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
//����ڰ� ��ǻ�͸� ��������μ� �������� ��� ������ 
//is_active �� true�� �ȴ�.

bool PC::StopUsing() {
	is_active = false;
	return true;
}
//����ڰ� ��ǻ�͸� ����� �������μ� �������� ��� ������ 
//is_active �� false�� �ȴ�.

bool PC::TurnOnComputer() {
	is_power_on = true;
	return true;
}}
//����ڰ� ��ǻ���� ������ �����μ� ���������� ��� ������ 
//is_power_on �� true�� �ȴ�.

bool PC::TurnOffComputer() {
	is_power_on = false;
	return true;
}
//����ڰ� ��ǻ���� ������ �����μ� ���������� ��� ������ 
//is_power_on �� false�� �ȴ�.
//code by Vincent