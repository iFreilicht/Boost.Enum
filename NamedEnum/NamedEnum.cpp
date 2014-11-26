// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef __INTELLISENSE__
#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1
#endif

#include "Examples.h"

#include <boost/preprocessor/config/config.hpp>


#include <iostream>
#include <supplies.hpp>
#include <advanced_enum_define.h>
#include <advanced_enum_adapt.h>
#include <boost/lexical_cast.hpp>

#include "macros/cat.h"
///---OR---


using boost::lexical_cast;
//using something::Action;
using namespace boost::advanced_enum;

enum class TestE{
	BOOST_ADVANCED_ENUM__NAME_COMMA((five, (5)))
	BOOST_ADVANCED_ENUM__NAME_COMMA((six))
	BOOST_ADVANCED_ENUM__NAME_COMMA((seven))
};

//Zott one = Zott::one;
namespace testing{
	enum Enum : int{
		zero,
		one,
		two,
		three,
		four
	};

	BOOST_ADVANCED_ENUM_ADAPT(Enum, int, 
		(zero)
		(one) 
		(two, "Zwo")
		(three) 
		(four)
	)

	BOOST_ADVANCED_ENUM_DEFINE(MyEnum, unsigned int,
		(zero)
		(one, _, "Eins")
		(two, _)
		(six, (6), "Sechs")
		(four)
	)
}





//void testLookup(){
//	Action action;
//	for (int i = 0; i < 200000; ++i){
//		action = lexical_cast<Action>("jump");
//	}
//}

//Many oneOfMany = Many::g;

int _tmain(int argc, _TCHAR* argv[])
{
	/*Action action;
	testLookup();
	something::Action_enum::init_lookupmaps();
	testLookup();
*/
	testing::Enum myEnum = lexical_cast<testing::Enum>("four");

	std::string enumStr = lexical_cast<std::string>(myEnum);

	/*Action jump = lexical_cast<Action>("jump");

	bool same = jump == action;

	std::string str = lexical_cast<std::string>(jump);

	std::cin >> action;

	bool same2 = jump == action;

	std::cout << action;
*/
	Many myMany = Many::Nz;

	example::AdaptLater adaEnum = lexical_cast<example::AdaptLater>("Zwanzig");

	adaEnum = example::AdaptLater::five;

	std::string adaStr = lexical_cast<std::string>(adaEnum);

	testing::MyEnum mEnum = lexical_cast<testing::MyEnum>("Sechs");

	mEnum = testing::MyEnum::one;

	std::string mStr = lexical_cast<std::string>(mEnum);


	return 0;
}

