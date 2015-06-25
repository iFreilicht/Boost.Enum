
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Examples for the use of the Boost.Enum DEFINE macros



//#define BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND 1

#include <boost/enum/define.hpp>
#include <boost/enum/options.hpp>

#include <boost/integer_traits.hpp>
#include <string>

namespace define_test{
	//bare minimum
	BOOST_ENUM_DEFINE(Zott,
		(zero)
		(one)
		(two)
		(three)
	)

	using namespace boost::enum_;


	//with options and custom values
	BOOST_ENUM_DEFINE_W_OPTIONS(LongNumber, (options<option_vals::roundtrip, long>),
		(minimum, (boost::integer_traits<long>::const_min))
		(zero, (0))
		(maximum, (boost::integer_traits<long>::const_min))
	)
	

	//with wide strings inside class
	class WideClass{
	public:
		BOOST_ENUM_DEFINE_IN_CLASS_I_W_OPTIONS(WideNames, (options<>::WithStringT<std::wstring>),
			(höhle, _, L"höhle")
			(fährte, _, L"fährte")
		)
	};
	BOOST_ENUM_DEFINE_IN_CLASS_II(WideClass::WideNames)


}