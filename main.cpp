#include <iostream>
#include <thread>
#include "PCManager.h"
#include "DBManager.h"
#include "Member.h"
int main() {
	PCManager::GetInstance()->Initialize();

	return 0;
}