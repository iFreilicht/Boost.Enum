
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "supply_selector.hpp"

namespace boost{
	namespace advanced_enum{
		

		/*inline Options operator | (Options rhs, Options lhs){
			return static_cast<Options>(static_cast<unsigned int>(rhs) | static_cast<unsigned int>(lhs));
		}

		inline Options operator & (Options rhs, Options lhs){
			return static_cast<Options>(static_cast<unsigned int>(rhs) & static_cast<unsigned int>(lhs));
		}

		inline Options operator ^ (Options rhs, Options lhs){
			return static_cast<Options>(static_cast<unsigned int>(rhs) ^ static_cast<unsigned int>(lhs));
		}

		inline Options operator ~ (Options operand){
			return static_cast<Options>(~ static_cast<unsigned int>(operand));
		}
*/
		struct OptionVals{
			enum : unsigned int{
				roundtrip = 1 << 0,
				is_flag = 1 << 1,
				arbitrary = 1 << 2,
				map_lookup = 1 << 3,
				no_ordering = 1 << 4
			};
		};

		template<unsigned int MyOptions = OptionVals::arbitrary, typename UnderlyingT = int, typename MySupply = supplies::NoCustomSupply, typename StringT = std::string>
		struct Options{
			static const bool roundtrip = static_cast<bool>(MyOptions & OptionVals::roundtrip | MyOptions & OptionVals::is_flag);
			static const bool is_flag = static_cast<bool>(MyOptions & OptionVals::is_flag);
			static const bool arbitrary = static_cast<bool>(MyOptions & OptionVals::arbitrary | MyOptions & OptionVals::roundtrip | MyOptions & OptionVals::is_flag);
			static const bool map_lookup = static_cast<bool>(MyOptions & OptionVals::map_lookup);
			static const bool no_ordering = static_cast<bool>(MyOptions & OptionVals::no_ordering);

			typedef typename ::boost::advanced_enum::supply_selector<UnderlyingT, MySupply, (bool)is_flag>::supply Supply;

			typedef UnderlyingT UnderlyingT;

			typedef StringT StringT;
		};
	}
}