#pragma once
/*
PC�濡�� �����Ǵ� PC �ϳ��� ���¸� ǥ���ϱ� ���� ������� Ŭ�����Դϴ�.
*/


class PC
{
private:
	int PC_Number;
	// ��ǻ���� ��뿩�θ� ǥ���մϴ�.
	bool is_active;
	// ��ǻ�� ������ ���� �ִ����� ���θ� ǥ���մϴ�.
	bool is_power_on;
	// ���� ����ڸ� ���մϴ�.
	class User* current_user;
public:
	PC(const int& number);
	~PC();
	// User�� �ش� PC ����� �����մϴ�.
	bool StartUsing(User* user);
	// USer�� �ش� PC ����� �����մϴ�.
	bool StopUsing();
	// User�� �ð��� �� ����Ǿ� ����� �ߴܵ˴ϴ�. �� �޼���� User���Լ� ȣ��˴ϴ�.
	bool AbortUsing();
	// ��ǻ�� ������ ŵ�ϴ�.
	bool TurnOnComputer();
	// ������ ���ϴ�.
	bool TurnOffComputer();
	bool GetPower_Status();
	bool Getactive_Status();
	User* GetUser();
};

