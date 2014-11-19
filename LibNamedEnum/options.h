
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace boost{
	namespace advanced_enum{
		enum class Options : unsigned int{
			roundtrip =		1 << 0,
			is_flag =		1 << 1,
			arbitrary =		1 << 2,
			map_lookup =	1 << 3
		};

		template<Options options>
		struct MyOptions{
			enum : bool { roundtrip = (unsigned int)options & (unsigned int)Options::roundtrip | (unsigned int)options & (unsigned int)Options::is_flag };
			enum : bool { is_flag = (unsigned int)options & (unsigned int)Options::is_flag };
			enum : bool { arbitrary = (unsigned int)options & (unsigned int)Options::arbitrary };
			enum : bool { map_lookup = (unsigned int)options & (unsigned int)Options::map_lookup };
		};
	}
}