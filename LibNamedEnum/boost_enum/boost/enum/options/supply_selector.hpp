
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ENUM_IG_SUPPLY_SELECTOR_HPP
#define BOOST_ENUM_IG_SUPPLY_SELECTOR_HPP

#include <boost/enum/options/supplies.hpp>

namespace boost{
	namespace enum_{
		template<typename UnderlyingT, typename Supply, bool is_flag>
		class supply_selector{
			//If the options define a supply, this one is used
			template<typename supply, bool is_flag>
			struct impl{
				typedef supply supply;
			};

			//If the options don't define a supply,
			//one needs to be selected based on the options flags
			template < bool is_flag >
			struct impl_no_supply;

			template<>
			struct impl_no_supply < false > {
				typedef supplies::increment<UnderlyingT> supply;
			};

			template<>
			struct impl_no_supply < true > {
				typedef supplies::shiftL1<UnderlyingT> supply;
			};

			//specialisation of impl for the empty supply argument
			template<bool is_flag>
			struct impl < supplies::NoCustomSupply, is_flag > {
				typedef typename impl_no_supply<is_flag>::supply supply;
			};

			
		public:
			typedef typename impl<Supply, is_flag>::supply supply;
		};
	}
}

#endif