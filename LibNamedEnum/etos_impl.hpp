
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "options.h"

namespace boost{
	namespace advanced_enum{
		template<Options Options_, typename EnumStorageT>
		class etos_impl{
			typedef typename EnumStorageT::UnderlyingT UnderlyingT;
			typedef std::string StringT;

			//linear_lookup
			template<typename CurrEntry>
			static StringT linear_lookup(UnderlyingT value){
				if (value == CurrEntry::value)
					return CurrEntry().name;
				else
					return linear_lookup<CurrEntry::prev>(value);
			}

			template<>
			static inline StringT linear_lookup<void>(UnderlyingT value){
				throw std::invalid_argument(std::to_string(value) + " is not a value in this enum.");
				return "";
			}

			//map_lookup
			static inline StringT map_lookup(UnderlyingT key){
				try{
					return EnumStorageT::instance().etosmap_.at(key);
				}
				catch (const std::out_of_range&){
					throw std::invalid_argument(std::to_string(key) + " is not a value in this enum.");
				}
			}

			//lookup
			template<bool Map_lookup>
			static inline StringT lookup(UnderlyingT val);

			template<>
			static inline StringT lookup<false>(UnderlyingT val){
				return linear_lookup<EnumStorageT::LastEntry>(val);
			}

			template<>
			static inline StringT lookup<true>(UnderlyingT val){
				return map_lookup(val);
			}


			//impl_f
			template<bool Roundtrip, bool Is_Flag, bool Map_lookup>
			struct impl_f{
				static inline StringT exec(UnderlyingT val);
			};

			template<bool Map_lookup>
			struct impl_f < false, false, Map_lookup > {
				static inline StringT exec(UnderlyingT val){
					return lookup<Map_lookup>(val);
				}
			};

			template<bool Map_lookup>
			struct impl_f < true, false, Map_lookup > {
				static inline StringT exec(UnderlyingT val){
					StringT ret;
					try{
						ret = lookup<Map_lookup>(val);
					}
					catch (const std::invalid_argument&){
						ret = std::to_string(val);
					}
					return ret;
				}
			};

			template<bool Map_lookup>
			struct impl_f < true, true, Map_lookup > {
				static inline StringT exec(UnderlyingT val){
					return lookup<Map_lookup>(val);
				}
			};
		public:
			static inline StringT f(UnderlyingT val){
				typedef MyOptions<Options_> opt;
				return impl_f < opt::roundtrip, opt::is_flag, opt::map_lookup >::exec(val);
			}
		};
	}
}