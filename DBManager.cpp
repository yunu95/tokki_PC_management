#include "DBManager.h"
#include "Member.h"
DBManager* DBManager::instance = nullptr;

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

