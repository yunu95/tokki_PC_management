#include <iostream>
#include <thread>
#include "PCManager.h"
#include "DBManager.h"
#include "Member.h"
int main() {
	//DBManager::GetInstance()->GetMemberinfo("fuck", "this");
	PCManager::GetInstance()->Initialize();

	return 0;
}