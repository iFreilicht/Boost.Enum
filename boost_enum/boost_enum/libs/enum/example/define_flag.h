
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND 1

#include <boost/enum/define_flag.hpp>
#include <boost/assert.hpp>
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
		Action actMove0 = Action::move;
		std::string strMove0 = "move";
		Action actMove1 = static_cast<Action>(strMove0);

		BOOST_ASSERT(actMove0 == actMove1);

		Actor actor0{ Actor::Action::move };
		Actor actor1{ static_cast<Actor::Action>(strMove0) };

		BOOST_ASSERT(actor0.get() == actor1.get());

		std::string strMoveThink0 = "move|think";
		Action actMoveThink0 = Action::move;
		actMoveThink0 |= Action::think;
		Action actMoveThink1 = static_cast<Action>(strMoveThink0);

		BOOST_ASSERT(actMoveThink0 == actMoveThink1);

		BOOST_ASSERT(actMoveThink0 & actMove0);

		BOOST_ASSERT(actMoveThink1 & Action::think);

		Action actMoveThink2 = static_cast<Action>("think|move");

		std::string strMoveThink2 = static_cast<std::string>(actMoveThink2);

		BOOST_ASSERT(actMoveThink2 == actMoveThink0);

		BOOST_ASSERT(strMoveThink2 == strMoveThink0);

		for (auto val : Action::values()){
			BOOST_ASSERT((Action)val == static_cast<Action>(static_cast<std::string>((Action)val)));
		}

		return true;
	}
};