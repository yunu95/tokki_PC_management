#include <iostream>
#include <cstring>
#include <WinSock2.h>
#pragma once
/*
���� DataBase�� ������ ã�� ��ȯ�ϰų� ������ ������Ʈ�����ش�.
*/
class Member;
class DBManager
{
private:
	// ���� �ν��Ͻ��� �ϳ��� �־�� �ϴ� Ŭ�����̹Ƿ�,
	// �ܺο��� �Ժη� �����ڰ� ȣ��Ǹ� �ȵǱ⿡ �����ڿ� �Ҹ��ڿ� private �����ڰ� �ٽ��ϴ�.
	DBManager();
	~DBManager();
	// �Ʒ��� �����ʹ� �� Ŭ������ ������ ��ü�� ����ŵ�ϴ�.
	static DBManager* instance;
	const char* IP = "210.94.181.91";
	const int PORT = 8029;
	const int BUFSIZE = 100;	

	SOCKET clientsock;
	WSADATA wsa;
	struct sockaddr_in sockinfo;

public:

	/*
	// �����ͺ��̽��� �ش� id,password�� �����ϴ� ����ڰ� �ִ��� Ȯ���Ѵ�.
	bool Login(std::string id,std::string password);
	// �����ͺ��̽��� info�� ���� ������ ������ Ʃ���� ���ٸ� ���� ��ȯ�Ѵ�.
	bool Register(Member& info);
	// DB�� ȸ���� ������ ID�� ���� ������ Member�ڷ������� ��ȯ�Ѵ�.
	Member GetMemberinfo(std::string ID);
	// DB�� ȸ���� ������ Ű���� ���� ������ Member�ڷ������� ��ȯ�Ѵ�.
	Member GetMemberinfo(int key);
	// DB�� �ִ� ȸ���� ������ ������Ʈ�Ѵ�. �����ϸ� false�� ��ȯ�Ѵ�.
	*/
	bool Recharge(char* id,char* time);
	//what register method needs | (name) | (age) | (phonenum) | (id) | (password)
	//	| (psw_question) | (psw_answer)

	bool Register(char* name, char* age, char* phonenum,char* id,char* passwd,char* question,char* psw_answer);
	bool Register(char* WholeMessage);
	bool AddTime(char* id, int time);
	bool Shutdown(char* id, int used_time);
	char* Login(char* wholeMessage);
	char* Login(char* id,char* password);
	// �̱��� ��ü�� ������ �ν��Ͻ��� �����ϱ� ���� ���̴� Getter�޼���.
	static DBManager* GetInstance();
};

/*
Login,Register�� ���� �̱��� ��ü�� �޼��带 ����ϰ� �ʹٸ�
GetInstance()->Login(... �̷������� ����� �� �ֽ��ϴ�.
*/