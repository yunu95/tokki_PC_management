#include "Member.h"


Member::Member(std::string id, std::string nowtime)
{
	this->id = id;//���̵�
	this->nowtime = nowtime;//�����ѽð�
}


Member::~Member()
{

}

void Member::AbortUsing(const PC& target)
{

}

void Member::SetLeftTime(const int& time) {
	this->left_time = time;//�����ð�
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