#include "Member.h"


Member::Member(std::string id, std::string nowtime)
{
	this->id = id;//아이디
	this->nowtime = nowtime;//시작한시간
}


Member::~Member()
{

}

void Member::AbortUsing(const PC& target)
{

}

void Member::SetLeftTime(const int& time) {
	this->left_time = time;//남은시간
}

std::string Member::GetIdentifier()
{
	return id;
}

int Member::GetLeftTime()
{
	return left_time;
}

char* Member::GetNowTime()
{
	return (char*)nowtime.c_str();
}