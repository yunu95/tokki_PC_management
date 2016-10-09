#pragma once
class User
{
private:
protected:
	// �����ڸ� protected�� ������ �� ���� User�� ���� �����Լ��� �� �ִ� Ŭ�����̹Ƿ�
	// �Ժη� �ν��Ͻ��� ��������� �ȵǱ� �����Դϴ�.
	User();
	~User();
public:
	class PC;
	// �Ʒ� �� �Լ��� ���� �����Լ��Դϴ�.
	// ���ð��� ����Ǿ��� �� target_pc���� �������Ḧ ��û�ϴ� �޼����Դϴ�.
	virtual void AbortUsing(const PC& target_pc) = 0;
	// ������� ���� �ð��� �����ϴ� �޼����Դϴ�.
	virtual void SetLeftTime(const float& time) = 0;
};
