// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Examples for the use of the Boost.Enum ADAPT macros

#include <boost/enum/adapt.hpp>
#include <boost/enum/options.hpp>

namespace adapt_test{
	enum class adaptit{
		zero,
		one,
		fourtyfive = 45,
		two = 2,
		banana = 20
	};

	BOOST_ENUM_ADAPT(adaptit,
		(zero)
		(one)
		(two)
		(banana)
		(fourtyfive)
	)


	enum class adaptflag{
		zero,
		dirty,
		exclusive,
		modified
	};

	BOOST_ENUM_ADAPT_W_OPTIONS(adaptflag, (boost::enum_::adapt_options<boost::enum_::option_vals::is_flag>), 
		(modified)
		(exclusive)
		(dirty)
		(zero)
	)
};

