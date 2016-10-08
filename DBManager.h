#include <iostream>
#include <cstring>
#pragma once
/*
���� DataBase�� ������ ã�� ��ȯ�ϰų� ������ ������Ʈ�����ش�.
*/
class DBManager
{
private:
	// ���� �ν��Ͻ��� �ϳ��� �־�� �ϴ� Ŭ�����̹Ƿ�,
	// �ܺο��� �Ժη� �����ڰ� ȣ��Ǹ� �ȵǱ⿡ �����ڿ� �Ҹ��ڿ� private �����ڰ� �ٽ��ϴ�.
	DBManager();
	~DBManager();
	// �Ʒ��� �����ʹ� �� Ŭ������ ������ ��ü�� ����ŵ�ϴ�.
	static DBManager* instance;
public:
	class Member;
	// �����ͺ��̽��� �ش� id,password�� �����ϴ� ����ڰ� �ִ��� Ȯ���Ѵ�.
	bool Login(std::string id,std::string password);
	// �����ͺ��̽��� info�� ���� ������ ������ Ʃ���� ���ٸ� ���� ��ȯ�Ѵ�.
	bool Register(Member& info);
	// DB�� ȸ���� ������ ID�� ���� ������ Member�ڷ������� ��ȯ�Ѵ�.
	Member GetMemberinfo(std::string ID);
	// DB�� ȸ���� ������ Ű���� ���� ������ Member�ڷ������� ��ȯ�Ѵ�.
	Member GetMemberinfo(int key);
	// DB�� �ִ� ȸ���� ������ ������Ʈ�Ѵ�. �����ϸ� false�� ��ȯ�Ѵ�.
	bool UpdateMemberinfo(const Member& info);
	// �̱��� ��ü�� ������ �ν��Ͻ��� �����ϱ� ���� ���̴� Getter�޼���.
	static DBManager* GetInstance();
};

/*
Login,Register�� ���� �̱��� ��ü�� �޼��带 ����ϰ� �ʹٸ�
GetInstance()->Login(... �̷������� ����� �� �ֽ��ϴ�.
*/