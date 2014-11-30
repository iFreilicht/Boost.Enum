
#pragma once

namespace something{
	namespace{
		struct Invisible{
			int x;
			explicit operator int() const{
				return x;
			}
		};

		int itoi(const Invisible& inv){
			return static_cast<int>(inv);
		}
	}
	typedef Invisible Visible;
}