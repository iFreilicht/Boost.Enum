
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_OPTIONS_HPP
#define BOOST_ENUM_IG_OPTIONS_HPP

#include <boost/enum/options/supply_selector.hpp>
#include <string>
#include <sstream>

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
				roundtrip = 1 << 0,			//conversions from value->string->value will always succeed
				is_flag = 1 << 1,			//every defined value represents a binary flag, conversions will break value down into 
				arbitrary = 1 << 2,			//values are not checked to be defined in the enum
				map_lookup = 1 << 3,		//lookup for conversions is performed in std::maps or similar strucutres
				no_ordering = 1 << 4		//comparison operators that allow ordering of the values will not be defined
			};
		};

		//The UnderlyingT argument is either of integral type for defined enums or the enum that is adapted
		template<unsigned int Options = option_vals::arbitrary, typename UnderlyingT = int, typename Supply = supplies::NoCustomSupply, typename StringT = std::string>
		struct options{
			static const bool roundtrip = static_cast<bool>(Options & option_vals::roundtrip | Options & option_vals::is_flag);
			static const bool is_flag = static_cast<bool>(Options & option_vals::is_flag);
			static const bool arbitrary = static_cast<bool>(Options & option_vals::arbitrary | Options & option_vals::roundtrip | Options & option_vals::is_flag);
			static const bool map_lookup = static_cast<bool>(Options & option_vals::map_lookup);
			static const bool no_ordering = static_cast<bool>(Options & option_vals::no_ordering);

			typedef typename ::boost::enum_::supply_selector<UnderlyingT, Supply, (bool)is_flag>::supply Supply;

			typedef UnderlyingT UnderlyingT;

			typedef StringT StringT;

			using istream_type = std::basic_istream < typename StringT::value_type, typename StringT::traits_type > ;

			using ostream_type = std::basic_ostream < typename StringT::value_type, typename StringT::traits_type > ;

			template<typename UnderlyingT>
			using WithUnderlyingT = options < Options, UnderlyingT, Supply, StringT > ;

			template<typename Supply>
			using WithSupply = options < Options, UnderlyingT, Supply, StringT >;

			template<typename StringT>
			using WithStringT = options < Options, UnderlyingT, Supply, StringT >;
		};

		template<unsigned int Options = option_vals::arbitrary, typename StringT = std::string>
		struct adapt_options{
			template<typename EnumT>
			struct options{
				typedef typename ::boost::enum_::options < Options, typename std::underlying_type<EnumT>::type, supplies::NoCustomSupply, StringT > type;
			};
		};
	}
}

#endif