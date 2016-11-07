#include <iostream>
#include <thread>
#include "PCManager.h"

int main() {
	PCManager::GetInstance()->LoadPCinfos();
	PCManager::GetInstance()->Initialize();

	return 0;
}