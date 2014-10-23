// NamedEnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Examples.h"

#include <iostream>

using something::Action;

Zott one = Zott::one;

int _tmain(int argc, _TCHAR* argv[])
{
	Action action = Action::jump;
	action = static_cast<Action>(7);

	std::cin >> action;

	std::cout << action;

	return 0;
}

