
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ENUM_IG_SUPPLIES_HPP
#define BOOST_ENUM_IG_SUPPLIES_HPP

namespace boost{
	namespace enum_{
		///Supplies are a concept used to provide values to enums.
		/** Supplies describe the convention on which the selection for underlying
		 * values of an enumeration is based. Regular C/C++-enums for example use
		 * an incrementing convention, starting at 0 and increasing for every new
		 * enum value defined.
		 * This is the same convention is described by supplies::increment.
		 * 
		 * A supply suitable for use with an enum is reuqired to have a certain structure,
		 * as demonstrated on the example of supplies::shiftL1<unsigned int>::values
		 * \code
		 *     template<unsigned int Val>
		 *     struct values{
		 *         enum : unsigned int{ next = Val << 1, start = 1 };
		 *     };
		 * \endcode
		 *
		 * In essence, a supply is a template, that
		 * * takes exactly one template parameter which is of integral type
		 * * has `start` of the same type as the template parameter defined
		 * * has `value` of the same type as the template parameter defined
		 * The two names `start` and `value` have the following function:
		 * `start` is the value the first enum value defined will have
		 * `next` is the value the next enum value after `Val`
		 * So in this case, values<8>::next == 16
		 *
		 * All supplies in this namespace are wrapped by another tempalted struct,
		 * which gives them the ability to apply to different integral types.
		 * This is not necessary for user-defined supplies, though. You are allowed to
		 * write a supply that only operates on `unsigned char`s, for example.
		*/
		namespace supplies{
			///Placeholder for when the supply should be selected by the compiler
			struct NoCustomSupply;

			///Shift left by 1, start at 1.
			template<typename UnderlyingT>
			struct shiftL1{
				typedef UnderlyingT UnderlyingT;
				template<UnderlyingT Index>
				struct values{
					typedef UnderlyingT UnderlyingT;
					enum : UnderlyingT{ value = 1 << Index };
				};
			};

			///Increment by 1, start at 0. Behaviour that normal enums use.
			template<typename UnderlyingT>
			struct increment{
				typedef UnderlyingT UnderlyingT;
				template<UnderlyingT Index>
				struct values{
					typedef UnderlyingT UnderlyingT;
					enum : UnderlyingT{ value = Index };
				};
			};
		}
	}
}

#endif //include guard