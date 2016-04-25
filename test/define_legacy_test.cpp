
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/enum/define_legacy.hpp>
#include <boost/enum/options.hpp>

//#define BOOST_TEST_MAIN
//#include <boost/test/unit_test.hpp>

#include <iostream>

using boost::enum_::options;
using boost::enum_::option_vals;

enum leg_unscoped {
	zero, one, two, ten = 10
};


BOOST_ENUM_DEFINE_LEGACY(ben_unscoped,
	(zero)
	(one)
	(two)
	(ten, (10))
);

void test_all(){
	leg_unscoped lu = ten;
	lu = leg_unscoped::ten;

	//ben_unscoped bu = ten; //not allowed yet, maybe shouldn't be. Seems to be hard to implement
	ben_unscoped bu = ben_unscoped::ten;

	unsigned long long ull = 4000;

	//---

	std::string lustr;
	std::string bustr;

	lustr = std::to_string(lu);
	std::cout << lustr << '\n';
	lustr = std::to_string((int)lu);
	std::cout << lustr << '\n';

	bustr = std::to_string(bu);
	std::cout << bustr << '\n';
	bustr = std::to_string((int)bu);
	std::cout << bustr << '\n';

	std::cin >> reinterpret_cast<int&>(lu);

	std::cin >> bu;

	//---

	std::cout << "\n\n";

	std::cout << lu << '\n';
	std::cout << (int)lu << '\n';

	std::cout << bu << '\n';
	std::cout << (int)bu << '\n';

	//---

	int luint;
	int buint;


	luint = lu;
	luint = (int)lu;
	luint = static_cast<int>(lu);

	buint = bu;
	buint = (int)bu;
	buint = static_cast<int>(bu);

	//---

	lu = (leg_unscoped)luint;
	lu = static_cast<leg_unscoped>(luint);
	//lu = (leg_unscoped)0.1234f;
	lu = (leg_unscoped)ull;
	//lu = (leg_unscoped)ls;

	bu = (ben_unscoped)buint;
	bu = static_cast<ben_unscoped>(buint);
	//bu = (ben_unscoped)0.1234f;
	bu = (ben_unscoped)ull;
	//bu = (ben_unscoped)lu;
}