
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#pragma once

namespace boost{
	namespace advanced_enum{
		template<typename EnumStorageT, bool map_lookup>
		struct instance_impl;
		
		template<typename EnumStorageT>
		struct instance_impl<EnumStorageT, false>{
			static EnumStorageT newInstance(){
				EnumStorageT storage{};
				return storage;
			}
		};

		template<typename EnumStorageT>
		struct instance_impl<EnumStorageT, true>{
			static EnumStorageT newInstance(){
				EnumStorageT storage{};
				storage.init_lookupmaps_non_static();
				return storage;
			}
		};
	}
}