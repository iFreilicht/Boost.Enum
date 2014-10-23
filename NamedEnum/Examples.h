#pragma once

#include <named_enum.h>

//example for a macro that uses ENUM_DEFINE_W_SUPPLY
#define DEFINE_FLAG_ENUM(enum_name, ...) BOOST_NAMED_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::named_enum::supplies::shiftL1, __VA_ARGS__)

//this is enough to define a named macro
BOOST_NAMED_ENUM_DEFINE(Zott,
	zero,
	one,
	two,
	three
	);

namespace something{
	DEFINE_FLAG_ENUM(Action,
		jump,
		look,
		move
		);
}

BOOST_NAMED_ENUM_DEFINE_W_SUPPLY(Numbers,
	BOOST_NAMED_ENUM_ARBITRARY_VALUES(5, 8, 20, 6, 41),
	five,
	eight,
	twenty,
	six,
	fortyone
	);