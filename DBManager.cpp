#include "DBManager.h"
#include "Member.h"
#include "Card.h"
DBManager* DBManager::instance = nullptr;

bool DBManager::UpdateMemberinfo(const Member & info)
{
	return false;
}

DBManager* DBManager::GetInstance() {
	if (instance)
		return instance;
	else
		return instance = new DBManager();
}
DBManager::DBManager()
{
}


DBManager::~DBManager()
{
}

Member* DBManager::GetMemberinfo(std::string ID) {
	return (Member*)(new Card(0));
}

Member * DBManager::GetMemberinfo(int key)
{
	return nullptr;
}
