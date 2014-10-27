// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Examples.h"

#include <iostream>

using something::Action;

//Zott one = Zott::one;


enum Enum : int{
	zero,
	one,
	two,
	three,
	four
};


bool not_true = one < zero;

void testLookup(){
	Action action;
	for (int i = 0; i < 200000; ++i){
		action = static_cast<Action>("jump");
	}
}

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

