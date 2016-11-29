#include <iostream>
#include <thread>
#include "PCManager.h"
#include "DBManager.h"
#include "Member.h"
int main() {
	DBManager::GetInstance()->Login("RedMenace","123456");
	DBManager::GetInstance()->Recharge("RedMenace", "101");
	DBManager::GetInstance()->Shutdown("RedMenace",100);
	PCManager::GetInstance()->Initialize();

	return 0;
}