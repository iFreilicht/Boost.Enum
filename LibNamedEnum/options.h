
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

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
				map_lookup = 1 << 3
			};
		};

		//used as standard argument for Options
		class NoCustomSupply;

		template<unsigned int MyOptions = OptionVals::arbitrary, typename UnderlyingT = int, typename MySupply = NoCustomSupply>
		struct Options{
			enum : bool { roundtrip = MyOptions & OptionVals::roundtrip | MyOptions & OptionVals::is_flag };
			enum : bool { is_flag = MyOptions & OptionVals::is_flag };
			enum : bool { arbitrary = MyOptions & OptionVals::arbitrary };
			enum : bool { map_lookup = MyOptions & OptionVals::map_lookup };

			//TODO: make this work
			//typedef typename supply_selector<UnderlyingT, MySupply, (bool)is_flag>::supply Supply;

			typedef typename supplies::increment < UnderlyingT > Supply;

			typedef UnderlyingT UnderlyingT;
		};
	}
}