// TestingStuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1

#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <macros/empty_argument.h>
#include "TestDecl.h"

using namespace something;



int _tmain(int argc, _TCHAR* argv[])
{

	Visible vis{};
	int i = itoi(vis);

	return 0;
}

