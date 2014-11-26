
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "options.h"
#include <string>

namespace boost{
	namespace advanced_enum{
		template<typename Options, typename EnumStorageT>
		class stoe_impl{
			typedef typename EnumStorageT::UnderlyingT UnderlyingT;
			typedef std::string StringT;

			//linear lookup
			template<typename CurrEntry>
			static UnderlyingT linear_lookup(const StringT& name){
				if (name == CurrEntry().name)
					return CurrEntry::value;
				else
					return linear_lookup<typename CurrEntry::prev>(name);
			}
			///Failure case when name is not the name of a value
			template<>
			static inline UnderlyingT linear_lookup<void>(const std::string& name){
				throw std::invalid_argument(name + " is not convertible to this enum.");
				return 0;
			}

			//map_lookup
			static UnderlyingT map_lookup(const StringT& name){
				try{
					return EnumStorageT::instance().stoemap_.at(name);
				}
				catch (const std::out_of_range&){
					throw std::invalid_argument(name + " is not convertible to this enum.");
				}
			}

			//lookup
			template<bool Map_lookup>
			static UnderlyingT lookup(const StringT& name);

			template<>
			static inline UnderlyingT lookup<false>(const StringT& name){
				return linear_lookup<EnumStorageT::LastEntry>(name);
			}

			template<>
			static inline UnderlyingT lookup<true>(const StringT& name){
				return map_lookup(name);
			}

			//impl_f
			template<bool Roundtrip, bool Is_flag, bool Map_lookup>
			struct impl_f;

			template<bool Map_lookup>
			struct impl_f<false, false, Map_lookup>{
				static inline UnderlyingT exec(const StringT& name){
					return lookup<Map_lookup>(name);
				}
			};

			template<bool Map_lookup>
			struct impl_f<true, false, Map_lookup>{
				static inline UnderlyingT exec(const StringT& name){
					UnderlyingT ret;
					try{
						ret = lookup<Map_lookup>(name);
					}
					catch (const std::invalid_argument&){
						ret = std::stoi(name);
					}
					return ret;
				}
			};

			template<bool Map_lookup>
			struct impl_f<true, true, Map_lookup>{
				static inline UnderlyingT exec(const StringT& name){
					return lookup<Map_lookup>(name);
				}
			};

		public:
			static inline UnderlyingT f(const StringT& name){
				return impl_f < Options::roundtrip, Options::is_flag, Options::map_lookup >::exec(name);
			}
		};
	}
}