
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND 1

#include <boost/enum/define_flag.hpp>
#include <string>

namespace define_flag_test{
	BOOST_ENUM_DEFINE_FLAG(Action,
		(move)
		(eat)
		(drink)
		(sleep)
		(think)
	)

	bool test(){
		Action act0 = Action::move;
		std::string str0 = "move";
		Action act1 = static_cast<Action>(str0);

		bool success = act0 == act1;

		std::string str1 = "move|think";
		act0 |= Action::think;
		Action act2 = static_cast<Action>(str1);

		success &= act0 == act2;

		success &= act0 & act1;

		success &= act0 & Action::think;

		Action act3 = static_cast<Action>("think|move");

		success &= act2 == act3;

		std::string str2 = static_cast<std::string>(act2);

		success &= str2 == str1;

		bool success4 = true;
		for (auto val : Action::values()){
			success4 &= (Action)val == static_cast<Action>(static_cast<std::string>((Action)val));
		}
		success &= success4;

		return success;
	}
};