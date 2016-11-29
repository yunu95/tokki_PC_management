#include "Member.h"


Member::Member(std::string id)
{
	this->id = id;
}


Member::~Member()
{

}

void Member::AbortUsing(const PC& target)
{

}

void Member::SetLeftTime(const float& time) {

}

std::string Member::GetIdentifier()
{
	return std::string("Member id : ") + id;
}
