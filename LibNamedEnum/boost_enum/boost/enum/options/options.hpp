
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

		//General behavioral options. For the option structs used with ADAPT and DEFINE macros, see boost::enum_::options and boost::enum_::adapt_options
		struct option_vals{
			enum : unsigned int{
				roundtrip = 1 << 0,			//conversions from value->string->value will always succeed
				is_flag = 1 << 1,			//every defined value represents a binary flag, conversions will break value down into 
				arbitrary = 1 << 2,			//values are not checked to be defined in the enum
				map_lookup = 1 << 3,		//lookup for conversions is performed in std::maps or similar strucutres
				no_ordering = 1 << 4		//comparison operators that allow ordering of the values will not be defined
			};
		};

		//Holds all options for use with the DEFINE macros, which are: (When using the ADAPT macro, please see boost::enum_::adapt_options)
		//
		// Options:
		//     General behavioral options, as defined in the enum option_vals.
		//
		// Underlyingt:
		//     The underlying integral type to be used for the enum.
		//
		// Supply:
		//     The Supply the underlying values of the enumeration values are generated from when the user doesn't define them explicitly. 
		//     They have to follow the guidelines specified in "supplies.hpp".
		//     NOTE: The standard value is not following this guidelines and is replaced with the increment supply or the shiftL1 supply if the option is_flag is set.
		//
		// StringT:
		//     The type of string to be used in the conversion. This allows for the use of non-case-sensitive strings and such. std::wstring is supported.
		//
		//-----------
		// Additionally, the WithUnderlyingT, WithSupply and WithStringT typedefs can be used when only one or of those arguments should differ from the standard ones.
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

		//Should be used with the ADAPT macro where fewer options are possible. In comparison to boost::enum_::options:
		//
		// Options:
		//     see options::Options
		//
		// StringT:
		//     see options::StringT
		//
		//----------
		// All options that adapt_options lacks are not applicable because they are determined from the adapted enum.
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