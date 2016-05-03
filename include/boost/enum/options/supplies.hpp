
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ENUM_IG_SUPPLIES_HPP
#define BOOST_ENUM_IG_SUPPLIES_HPP

namespace boost{
	namespace enum_{
		//! Supplies are a concept used to provide values to enums.
		/*! Supplies describe the convention on which the selection for underlying
			values of an enumeration is based. Regular C/C++-enums for example use
			an incrementing convention, starting at 0 and increasing for every new
			enum value defined.
			This same convention is described by supplies::increment.
			
			In essence, a supply is a class that has the following form:
			\code
				struct *supplyName*{
					typedef *integral type* UnderlyingT;
					template<UnderlyingT Index>
					struct values{
						typedef UnderlyingT UnderlyingT;
						enum : UnderlyingT{ value = *Calculation of value* };
					};
				};
			\endcode

			`Index` will be 0 for the first value in the enum, 1 for the second and so on.

			The value of the previously defined enumeration value can NOT be accessed due to technical limitations.

			Additional names are allowed to exist inside a supply, but should be kept private when possible.
			The supply can also be a class template as shown with shiftL1 and increment, 
			but enum_::options still needs a class as its argument, so the template needs to be instantiated.
		*/
		namespace supplies{
			//! Placeholder for when the supply should be selected by the compiler
			struct NoCustomSupply;

			//! Shift left by 1, start at 1.
			template<typename UnderlyingT>
			struct shiftL1{
				typedef UnderlyingT UnderlyingT;
				template<UnderlyingT Index>
				struct values{
					typedef UnderlyingT UnderlyingT;
					enum : UnderlyingT{ value = 1 << Index };
				};
			};

			//! Increment by 1, start at 0. Behaviour that normal enums use.
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