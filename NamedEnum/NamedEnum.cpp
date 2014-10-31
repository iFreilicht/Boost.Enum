// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Examples.h"

#include <iostream>
#include <advanced_enum.h>
#include <advanced_enum2.h>

using something::Action;

//Zott one = Zott::one;

Zot graf = Zot::zero;


enum Enum : int{
	zero,
	one,
	two,
	three,
	four
};

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



	Action jump = action;

	bool same = jump == action;

	std::string str = static_cast<std::string>(jump);

	std::cin >> action;

	bool same2 = jump == action;

	std::cout << action;

	return 0;
}

