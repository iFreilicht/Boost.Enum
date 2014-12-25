
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_OPTIONS_HPP
#define BOOST_ENUM_IG_OPTIONS_HPP

#include <boost/enum/options/supply_selector.hpp>

namespace boost{
	namespace enum_{
		

		/*inline options operator | (options rhs, options lhs){
			return static_cast<options>(static_cast<unsigned int>(rhs) | static_cast<unsigned int>(lhs));
		}

		inline options operator & (options rhs, options lhs){
			return static_cast<options>(static_cast<unsigned int>(rhs) & static_cast<unsigned int>(lhs));
		}

		inline options operator ^ (options rhs, options lhs){
			return static_cast<options>(static_cast<unsigned int>(rhs) ^ static_cast<unsigned int>(lhs));
		}

		inline options operator ~ (options operand){
			return static_cast<options>(~ static_cast<unsigned int>(operand));
		}
*/
		struct option_vals{
			enum : unsigned int{
				roundtrip = 1 << 0,
				is_flag = 1 << 1,
				arbitrary = 1 << 2,
				map_lookup = 1 << 3,
				no_ordering = 1 << 4
			};
		};

		//The UnderlyingT argument is either of integral type for defined enums or the enum that is adapted
		template<unsigned int MyOptions = option_vals::arbitrary, typename UnderlyingT = int, typename MySupply = supplies::NoCustomSupply, typename StringT = std::string>
		struct options{
			static const bool roundtrip = static_cast<bool>(MyOptions & option_vals::roundtrip | MyOptions & option_vals::is_flag);
			static const bool is_flag = static_cast<bool>(MyOptions & option_vals::is_flag);
			static const bool arbitrary = static_cast<bool>(MyOptions & option_vals::arbitrary | MyOptions & option_vals::roundtrip | MyOptions & option_vals::is_flag);
			static const bool map_lookup = static_cast<bool>(MyOptions & option_vals::map_lookup);
			static const bool no_ordering = static_cast<bool>(MyOptions & option_vals::no_ordering);

			typedef typename ::boost::enum_::supply_selector<UnderlyingT, MySupply, (bool)is_flag>::supply Supply;

			typedef UnderlyingT UnderlyingT;

			typedef StringT StringT;
		};

		template<unsigned int MyOptions = option_vals::arbitrary, typename StringT = std::string>
		struct adapt_options{
			template<typename EnumT>
			struct options{
				typedef typename ::boost::enum_::options < MyOptions, typename std::underlying_type<EnumT>::type, supplies::NoCustomSupply, StringT > type;
			};
		};
	}
}

#endif