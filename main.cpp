#include <iostream>
#include <thread>
#include "PCManager.h"
#include "DBManager.h"
#include "Member.h"
int main()
{
	//DBManager::GetInstance()->Register("m|bucklin|12|01053689814|forfuck|b773bf29f1683|what the fuck should i do|damn|wlwhs1126@naver.com");
	//DBManager::GetInstance()->Register("m|bucklin|12|01053689814|forfuck'ssake|b773bf29f1683ae506c01057984eb9107cb1487517b468f6dab953bb09312833|what the fuck should i do|damn");

	PCManager::GetInstance()->Initialize();

	return 0;
}
