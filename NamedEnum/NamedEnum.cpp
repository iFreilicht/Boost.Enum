// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#define BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND 1

#include "Examples.h"

#include <boost/preprocessor/config/config.hpp>


#include <iostream>
#include <boost/enum/adapt.hpp>
#include <boost/enum/define.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/enum/options/options.hpp>

#include <libs/enum/example/define.h>
#include <libs/enum/example/define_flag.h>


using boost::lexical_cast;
//using namespace something;
typedef ClassWithAction::Action Action;
using namespace boost::enum_;

//Zott one = Zott::one;
namespace testing{
	enum Enum : int{
		zero,
		one,
		two,
		three,
		four
	};

	BOOST_ENUM_ADAPT_W_OPTIONS(Enum, (adapt_options<option_vals::is_flag>), 
		(zero)
		(one) 
		(two, "Zwo")
		(three) 
		(four)
	)

	BOOST_ENUM_DEFINE_W_OPTIONS(MyEnum, (options<option_vals::map_lookup | option_vals::roundtrip, unsigned int>),
		(zero)
		(one, _, "Eins")
		(two, _)
		(six, (6), "Sechs")
		(four)
	)
}

void testLookup(){
	Action action;
	for (int i = 0; i < 200000; ++i){
		action = lexical_cast<Action>("jump");
	}
}

//Many oneOfMany = Many::g;

int _tmain(int argc, _TCHAR* argv[])
{
	bool define_flag_success = define_flag_test::test();
	//<Action>

	Action action{};
	//testLookup();

	Action sleep = Action::sleep;

	action = Action::move;
	action |= sleep;

	BOOST_ASSERT(action == (Action)(Action::sleep | Action::move));

	action = Action(Action::drink) | Action::eat;
	action = Action::drink | Action(Action::jump);
	action = Action::drink | Action::sleep;

	BOOST_ASSERT((unsigned int)action == ((unsigned int)Action::drink | (unsigned int)Action::sleep));

	bool is_drink = static_cast<bool>(Action::drink & action);

	BOOST_ASSERT(is_drink);

	std::string combinedStr = static_cast<std::string>(action);

	Action action2 = static_cast<Action>(combinedStr);

	BOOST_ASSERT(action2 == action);

	combinedStr = lexical_cast<std::string>(action);

	action2 = lexical_cast<Action>(combinedStr);

	BOOST_ASSERT(action2 == action);

	//</Action>

	testing::Enum myEnum = lexical_cast<testing::Enum>("four");
	testing::Enum_e myEnum2 = myEnum;

	std::string enumStr = lexical_cast<std::string>(myEnum);

	Many myMany = Many::Nz;

	//example::AdaptLater adaEnum = lexical_cast<example::AdaptLater>("Zwanzig");

	//adaEnum = example::AdaptLater::five;

	//std::string adaStr = lexical_cast<std::string>(adaEnum);

	testing::MyEnum mEnum = lexical_cast<testing::MyEnum>("Sechs");
	//testing::MyEnum mEnum2 = static_cast<testing::MyEnum>("Sechs");

	mEnum = testing::MyEnum::one;

	std::string mStr = lexical_cast<std::string>(mEnum);
	std::string mStr2 = static_cast<std::string>(mEnum);

	return 0;
}

