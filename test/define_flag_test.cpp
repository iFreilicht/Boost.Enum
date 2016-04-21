
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/enum/define_flag.hpp>

class ClassWithAction {
public:
	BOOST_ENUM_DEFINE_FLAG_IN_CLASS_I(Action,
		(jump)
		(look)
		(move)
		(eat)
		(drink)
		(sleep)
		(think)
	)
};

BOOST_ENUM_DEFINE_FLAG_IN_CLASS_II(ClassWithAction::Action)


void test_all()
{
	typedef ClassWithAction::Action Action;
	Action::has_value((Action::UnderlyingT)Action::think);
	Action::has_value(((Action::UnderlyingT)Action::think + 1));
}