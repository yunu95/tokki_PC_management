#pragma once
/*
PC�濡�� �����Ǵ� PC �ϳ��� ���¸� ǥ���ϱ� ���� ������� Ŭ�����Դϴ�.
*/


class PC
{
private:
	// ��ǻ���� ��뿩�θ� ǥ���մϴ�.
	bool is_active;
	// ��ǻ�� ������ ���� �ִ����� ���θ� ǥ���մϴ�.
	bool is_power_on;
	// ���� ����ڸ� ���մϴ�.
	class User* current_user;
public:
	PC();
	~PC();
	// User�� �ش� PC ����� �����մϴ�.
	bool StartUsing();
	// USer�� �ش� PC ����� �����մϴ�.
	bool StopUsing();
	// User�� �ð��� �� ����Ǿ� ����� �ߴܵ˴ϴ�. �� �޼���� User���Լ� ȣ��˴ϴ�.
	bool AbortUsing();
	// ��ǻ�� ������ ŵ�ϴ�.
	bool TurnOnComputer();
	// ������ ���ϴ�.
	bool TurnOffComputer();
};

