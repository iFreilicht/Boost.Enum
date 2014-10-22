// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "named_enum.h"

std::string one = Zott_enum::etos<Zott::one>();


int _tmain(int argc, _TCHAR* argv[])
{
	Numbers_enum::init_lookupmaps();
	auto eight = Numbers_enum::stoe("eight");
	return 0;
}

