#pragma once
#include <string>
#include "User.h"
/*
ȸ�������ؼ� ���̵�� ����� ��� �� �ִ� User�� ǥ���մϴ�.
db�� �ִ� Ʃ���� ������ �״�� Ŭ���̾�Ʈ ��ü�� ������Ű�� ���� Ŭ�����Դϴ�.
*/
class PC;
class Member :
	public User
{
private:
	// ����ڿ��� ���� �ð��Դϴ�.
	float left_time;
	std::string id;
public:
	// Ʃ���� ������ �״�� ������ �˴ϴ�.
	Member(std::string id);
	~Member();
	// �ð��� �� �Ǿ��� �� �ߵ��Ǵ� �޼����Դϴ�. target PC���� �������Ḧ ��û�ϰ�,
	// DB���� ���� �ð��� �����ϴ� �� ���� ��û�ؾ� �մϴ�.
	virtual void AbortUsing(const PC& target) override;
	virtual void SetLeftTime(const float& time) override;
	virtual std::string GetIdentifier() override;
	virtual float GetLeftTime() override;
};

