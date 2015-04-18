
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND 1

#include <boost/enum/define_flag.hpp>
#include <string>

namespace define_flag_test{
	//bare minimum
	BOOST_ENUM_DEFINE_FLAG(Action,
		(move)
		(eat)
		(drink)
		(sleep)
		(think)
	)

	//inside class
	class Actor{
	public:
		BOOST_ENUM_DEFINE_FLAG_IN_CLASS_I(Action,
			(move)
			(eat)
			(drink)
			(sleep)
			(think)
		)

		Actor(Action action) : action_(action){}

		Action get(){ return action_; }
		void set(Action action){ action_ = action; }
	private:
		Action action_;
	};

	BOOST_ENUM_DEFINE_FLAG_IN_CLASS_II(Actor::Action)

	//examples on usage
	bool test(){
		Action act0 = Action::move;
		std::string str0 = "move";
		Action act1 = static_cast<Action>(str0);

		bool success = act0 == act1;

		Actor a0{ Actor::Action::move };
		Actor a1{ static_cast<Actor::Action>(str0) };

		success &= a0.get() == a1.get();

		std::string str1 = "move|think";
		act0 |= Action::think;
		Action act2 = static_cast<Action>(str1);

		success &= act0 == act2;

		success &= act0 & act1;

		success &= act0 & Action::think;

		Action act3 = static_cast<Action>("think|move");

		success &= act2 == act3;

		std::string str2 = static_cast<std::string>(act2);

		success &= str2 == str1;

		bool success4 = true;
		for (auto val : Action::values()){
			success4 &= (Action)val == static_cast<Action>(static_cast<std::string>((Action)val));
		}
		success &= success4;

		return success;
	}
};