#include "PCManager.h"

PCManager* PCManager::instance = nullptr;

PCManager* PCManager::GetInstance() {
	if (instance)
		return instance;
	else
		return instance = new PCManager();
}

PCManager::PCManager()
{
}


PCManager::~PCManager()
{
}