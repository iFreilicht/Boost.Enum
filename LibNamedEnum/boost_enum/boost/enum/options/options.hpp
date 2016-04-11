
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

		//! General behavioral options. 
		/*!
			For the option structs used with ADAPT and DEFINE macros, see enum_::options and enum_::adapt_options

			These options are regular boolean flags, packed into an enum for easier naming.
		*/
		struct option_vals{
			enum : unsigned int{
				use_default = 0,
				//! Conversions from value->string->value will always succeed. 
				/*!
					This is true even if value isn't defined in the enumeration.
					If is_flag is not set, that means that a conversion from a value not in the enum to a string
					will yield the string representation of the underlying value.
				*/
				roundtrip = 1 << 0,

				//! Every defined value represents a binary flag. 
				/*!
					This means that binary operators are defined for the enum and that
					conversions to a string will also show each flag value seperately, which also implies
					roundtrip conversions.
				*/
				is_flag = 1 << 1,

				//! Values are not checked against being defined in the enumeration.
				/*!
					This also means that the enumeration can be casted from its underlying type,
					but it doesn't imply roundtrip conversion.
				*/
				arbitrary = 1 << 2,

				//! Lookup for conversions is performed in std::maps or similar strucutres.
				/*!
					This increases performance greatly but also requires more than double the memory,
					which may not be desirable in some cases.
				*/
				map_lookup = 1 << 3,

				//! Comparison operators that allow ordering of the values will not be defined.
				/*!
					In particular, `>`, `>=`, `<=` and `<`, which are available by default, won't be defined.
					With that, the enumeration also loses the ability to act as an index in collections that
					require (some of) these operators to be defined.
				*/
				no_ordering = 1 << 4
			};
		};

		//! Holds all options for use with the DEFINE macros. 
		/*!
			\note When using ADAPT macros, refer to enum_::adapt_options
			
			\tparam Options 
				General behavioral options, as defined in enum_::option_vals.
			
			\tparam UnderlyingT 
				The underlying integral type to be used for the enum.
			
			\tparam Supply 
				A rule the underlying values of the enumeration values are generated after when the user doesn't define them explicitly. 
			    They have to follow the guidelines specified in supplies.hpp
				The standard value of \a Supply is a placeholder and is swapped out following the rules of enum_::supply_selector
			    
			\tparam StringT
			    The type of string to be used in the conversion. This allows for the use of non-case-sensitive strings and such. 
				`std::wstring` is supported, see "WString support [TODO]" for more information


			`WithUnderlyingT`, `WithSupply` and `WithStringT` typedefs can be used when only those arguments should differ from the default ones like so:

			    typedef my_cool_options boost::enum_::options<>::WithUnderlyingT<unsigned char>;
		*/
		template<unsigned int Options = option_vals::use_default, typename UnderlyingT = int, typename Supply = supplies::NoCustomSupply, typename StringT = std::string>
		struct options{
			//! \copybrief enum_::option_vals::roundtrip
			static const bool roundtrip = static_cast<bool>(Options & option_vals::roundtrip | Options & option_vals::is_flag);
			//! \copybrief enum_::option_vals::is_flag
			static const bool is_flag = static_cast<bool>(Options & option_vals::is_flag);
			//! \copybrief enum_::option_vals::arbitrary
			static const bool arbitrary = static_cast<bool>(Options & option_vals::arbitrary | Options & option_vals::roundtrip | Options & option_vals::is_flag);
			//! \copybrief enum_::option_vals::map_lookup
			static const bool map_lookup = static_cast<bool>(Options & option_vals::map_lookup);
			//! \copybrief enum_::option_vals::no_ordering
			static const bool no_ordering = static_cast<bool>(Options & option_vals::no_ordering);

			typedef typename ::boost::enum_::supply_selector<UnderlyingT, Supply, (bool)is_flag>::supply Supply;

			typedef UnderlyingT UnderlyingT;

			typedef StringT StringT;

			using istream_type = std::basic_istream < typename StringT::value_type, typename StringT::traits_type > ;

			using ostream_type = std::basic_ostream < typename StringT::value_type, typename StringT::traits_type > ;

			//! Equivalent to options with UnderlyingT applied. Can be chained with WithSupply and WithStringT
			template<typename UnderlyingT>
			using WithUnderlyingT = options < Options, UnderlyingT, Supply, StringT > ;

			//! Equivalent to options with Supply applied. Can be chained with WithUnderlyingT and WithStringT
			template<typename Supply>
			using WithSupply = options < Options, UnderlyingT, Supply, StringT >;

			//! Equivalent to options with StringT applied. Can be chained with WithUnderlyingtT and WithSupply.
			template<typename StringT>
			using WithStringT = options < Options, UnderlyingT, Supply, StringT >;
		};

		//! Holds all options for use with the ADAPT macros. 
		/*!
			adapt_options is pretty much a stripped down version of enum_::options, but they can't be used interchangably.
			An adapted enumerations options instance will still be deduced from the regular options template.

			\tparam Options 
				General behavioral options, as defined in the enum option_vals.
			
			\tparam StringT
				The type of string to be used in the conversion. This allows for the use of non-case-sensitive strings and such. 
				`std::wstring` is supported, see "WString support [TODO]" for more information.
				Enums with values that have special characters in them that would normally be made available by wstring are not tested yet.

			All options that adapt_options lacks are not applicable because they are determined from the adapted enum.
		*/
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