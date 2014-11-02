// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Examples.h"

#include <iostream>
//#include <advanced_enum.h>
#include <advanced_enum_define.h>
#include <advanced_enum_adapt.h>
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;
using something::Action;
using namespace boost::advanced_enum;

//Zott one = Zott::one;
namespace testing{
	enum class Enum : int{
		zero,
		one,
		two,
		three,
		four
	};

	BOOST_ADVANCED_ENUM_ADAPT(Enum, int, (zero), (one), (two), (three), (four))
}



void testLookup(){
	Action action;
	for (int i = 0; i < 200000; ++i){
		action = static_cast<Action>("jump");
	}
}

Many oneOfMany = Many::g;

int _tmain(int argc, _TCHAR* argv[])
{
	Action action;
	testLookup();
	Action::init_lookupmaps();
	testLookup();

	testing::Enum myEnum = lexical_cast<testing::Enum>("four");

	std::string enumStr = lexical_cast<std::string>(myEnum);

	Action jump = lexical_cast<Action>("jump");

	bool same = jump == action;

	std::string str = lexical_cast<std::string>(jump);

	std::cin >> action;

	bool same2 = jump == action;

	std::cout << action;

	return 0;
}

