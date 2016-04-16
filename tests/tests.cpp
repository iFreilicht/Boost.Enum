// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#define BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND 1

#include <string>
#include <iostream>

#include <boost/enum/define.hpp>
#include <boost/enum/define_flag.hpp>
#include <boost/enum/define_legacy.hpp>

//#include "Examples.h"

#pragma once

//leg_unscoped and ben_unscoped should have as similar behaviour as possible

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

//leg_scoped and leg_unscoped should have as similar behaviour as possible

enum class leg_scoped {
	zero, one, two, ten = 10
};

BOOST_ENUM_DEFINE_W_OPTIONS(ben_scoped,
	(options<option_vals::use_default>),
	(zero)
	(one)
	(two)
	(ten, (10))
);



int _tmain(int argc, _TCHAR* argv[])
{
	leg_unscoped lu = ten;
	lu = leg_unscoped::ten;

	//ben_unscoped bu = ten; //not allowed yet, maybe shouldn't be. Seems to be hard to implement
	ben_unscoped bu = ben_unscoped::ten;

	leg_scoped ls = leg_scoped::ten;

	ben_scoped bs = ben_scoped::ten;

	unsigned long long ull = 4000;

	//---

	std::string lustr;
	std::string bustr;
	std::string lsstr;
	std::string bsstr;

	lustr = std::to_string(lu);
	std::cout << lustr << '\n';
	lustr = std::to_string((int)lu);
	std::cout << lustr << '\n';

	bustr = std::to_string(bu);
	std::cout << bustr << '\n';
	bustr = std::to_string((int)bu);
	std::cout << bustr << '\n';

	//lsstr = std::to_string(ls); //not allowed
	lsstr = std::to_string((int)ls);

	//bsstr = std::to_string(bs); //not allowed yet, maybe shouldn't be. Would be hard to implement.
	bsstr = std::to_string((int)bs);

	//std::stringstream luss;
	//std::stringstream buss;
	//std::stringstream lsss;
	//std::stringstream bsss;

	//luss << 10;
	//luss >> (int&)lu;

	//buss << 10;
	//buss >> (int&)bu;
	//buss << 10;
	//buss >> bu;

	//lsss << 10;
	//lsss >> (int&)ls;
	//
	//bsss << 10;
	//bsss >> (int&)bs;
	//bsss << 10;
	//bsss >> bs;

	bool fail = false;

	std::cin >> reinterpret_cast<int&>(lu);

	std::cin >> bu;

	std::cin >> reinterpret_cast<int&>(ls);
	
	std::cin >> bs;

	//---

	std::cout << "\n\n";

	std::cout << lu << '\n';
	std::cout << (int)lu << '\n';

	std::cout << bu << '\n';
	std::cout << (int)bu << '\n';

	std::cout << /*ls<<*/ '\n'; //not allowed
	std::cout << (int)ls << '\n';

	std::cout << bs << '\n';
	std::cout << (int)bs << '\n';

	//---

	int luint;
	int buint;
	int lsint;
	int bsint;

	luint = lu;
	luint = (int)lu;
	luint = static_cast<int>(lu);

	buint = bu;
	buint = (int)bu;
	buint = static_cast<int>(bu);

	//lsint = ls; //not allowed
	lsint = (int)ls;
	lsint = static_cast<int>(ls);

	//bsint = bs; //not allowed
	bsint = (int)bs;
	bsint = static_cast<int>(lu);

	//TODO: add casts for other integral types

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

	ls = (leg_scoped)lsint;
	ls = static_cast<leg_scoped>(lsint);
	//ls = (leg_scoped)0.1234f;
	ls = (leg_scoped)ull;
	//ls = (leg_scoped)lu;

	bs = (ben_scoped)bsint;
	bs = static_cast<ben_scoped>(bsint);
	//bs = (ben_scoped)0.1234f;
	//bs = (ben_scoped)ull;		//throws exception
	//bs = (ben_scoped)ls;

	//--- The following section is not working fine at all, maybe it doesn't have to

	leg_unscoped* lu_p = &lu;
	ben_unscoped* bu_p = &bu;
	leg_scoped* ls_p = &ls;
	ben_scoped* bs_p = &bs;
	int* luint_p;
	int* buint_p;
	int* lsint_p;
	int* bsint_p;


	luint_p = reinterpret_cast<int*>(lu_p);
	lu_p = reinterpret_cast<leg_unscoped*>(luint_p);

	buint_p = reinterpret_cast<int*>(bu_p);
	bu_p = reinterpret_cast<ben_unscoped*>(luint_p);

	lsint_p = reinterpret_cast<int*>(ls_p);
	ls_p = reinterpret_cast<leg_scoped*>(lsint_p);

	bsint_p = reinterpret_cast<int*>(bs_p);
	bs_p = reinterpret_cast<ben_scoped*>(lsint_p);

	
	

	return 0;
}
