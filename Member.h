#pragma once
#include "User.h"
/*
ȸ�������ؼ� ���̵�� ����� ��� �� �ִ� User�� ǥ���մϴ�.
db�� �ִ� Ʃ���� ������ �״�� Ŭ���̾�Ʈ ��ü�� ������Ű�� ���� Ŭ�����Դϴ�.
*/
class Member :
	public User
{
private:
	// ����ڿ��� ���� �ð��Դϴ�.
	float left_time;
public:
	// Ʃ���� ������ �״�� ������ �˴ϴ�.
	Member();
	~Member();
	class PC;
	// �ð��� �� �Ǿ��� �� �ߵ��Ǵ� �޼����Դϴ�. target PC���� �������Ḧ ��û�ϰ�,
	// DB���� ���� �ð��� �����ϴ� �� ���� ��û�ؾ� �մϴ�.
	void AbortUsing(const PC& target);
};

