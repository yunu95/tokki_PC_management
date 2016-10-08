#include <iostream>
#include <cstring>
#pragma once
/*
원격 DataBase의 정보를 찾아 반환하거나 정보를 업데이트시켜준다.
*/
class DBManager
{
private:
	// 오직 인스턴스가 하나만 있어야 하는 클래스이므로,
	// 외부에서 함부로 생성자가 호출되면 안되기에 생성자와 소멸자에 private 한정자가 붙습니다.
	DBManager();
	~DBManager();
	// 아래의 포인터는 이 클래스의 유일한 객체를 가리킵니다.
	static DBManager* instance;
public:
	class Member;
	// 데이터베이스에 해당 id,password를 만족하는 사용자가 있는지 확인한다.
	bool Login(std::string id,std::string password);
	// 데이터베이스에 info와 같은 정보를 가지는 튜플이 없다면 참을 반환한다.
	bool Register(Member& info);
	// DB의 회원의 정보를 ID를 통해 가져와 Member자료형으로 반환한다.
	Member GetMemberinfo(std::string ID);
	// DB의 회원의 정보를 키값을 통해 가져와 Member자료형으로 반환한다.
	Member GetMemberinfo(int key);
	// DB에 있는 회원의 정보를 업데이트한다. 실패하면 false를 반환한다.
	bool UpdateMemberinfo(const Member& info);
	// 싱글톤 객체의 유일한 인스턴스를 참조하기 위해 쓰이는 Getter메서드.
	static DBManager* GetInstance();
};

/*
Login,Register와 같은 싱글톤 객체의 메서드를 사용하고 싶다면
GetInstance()->Login(... 이런식으로 사용할 수 있습니다.
*/