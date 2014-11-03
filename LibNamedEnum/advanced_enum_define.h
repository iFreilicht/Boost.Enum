#pragma once

#include "advanced_enum_base.h"
#include "enum_storage.hpp"

#define BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name)				\
namespace {																\
	namespace BOOST_PP_CAT(_artifacts_,enum_name){									\

#define BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING(name)						\
		char name[] = #name;										\

#define BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(supply, ...)			\
		typedef ::boost::advanced_enum::enum_storage<supply<0>::UnderlyingT, supply>::gen<__VA_ARGS__>::get enum_storage;						\
		enum class index : enum_storage::SizeT{						\

#define BOOST_ADVANCED_ENUM__DEFINE_INDEX(name)								\
			name,													\

#define BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION			\
		};															\
		enum class Values{										\

#define BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE(enum_name, name)										\
			name = enum_storage::													\
				value_at<static_cast<enum_storage::SizeT>(index::name)>::value,		\

#define BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)	\
		};																\
		typedef ::boost::advanced_enum::advanced_enum_base			\
			<enum_storage, Values> Base;					\
	}																\
}																	\
typedef BOOST_PP_CAT(_artifacts_,enum_name)::Values enum_name;		\
struct  BOOST_PP_CAT(enum_name, _enum) : BOOST_PP_CAT(_artifacts_, enum_name)::Base{		\
	BOOST_PP_CAT(enum_name, _enum)() : BOOST_PP_CAT(_artifacts_,enum_name)::Base(){}									\
	BOOST_PP_CAT(enum_name, _enum)(ValueT v) : BOOST_PP_CAT(_artifacts_,enum_name)::Base(v){}						\
	explicit BOOST_PP_CAT(enum_name, _enum)(UnderlyingT v) : BOOST_PP_CAT(_artifacts_,enum_name)::Base(v){}			\
	explicit BOOST_PP_CAT(enum_name, _enum)(const std::string& s) : BOOST_PP_CAT(_artifacts_,enum_name)::Base(s){}	\
};																								\
inline std::istream& operator >>(std::istream& lhs, enum_name& rhs){								\
	std::string s;																				\
	lhs >> s;																				\
	try{																					\
		rhs = static_cast<BOOST_PP_CAT(enum_name, _enum)>(s);												\
		}																						\
	catch (const std::invalid_argument&){}													\
	return lhs;																				\
}																							\
inline std::ostream& operator <<(std::ostream& lhs, enum_name rhs){						\
	return lhs << static_cast<std::string>((BOOST_PP_CAT(enum_name, _enum)) rhs);			\
}

///Define an advanced_enum with a supply
/**
\sa #BOOST_ADVANCED_ENUM_DEFINE
*/
#define BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, supply, ...)									\
		BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name)											\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING, __VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(supply, __VA_ARGS__)							\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_INDEX, __VA_ARGS__)			\
		BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION												\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE,__VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)												\

///Define an advanced_enum without using a supply, with int increments
/**This macro is just for convenience when you don't want to manually
* specify a supply.
*/
#define BOOST_ADVANCED_ENUM_DEFINE(enum_name, ...) BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::advanced_enum::supplies::increment<int>::values, __VA_ARGS__)

#define BOOST_ADVANCED_ENUM_ARBITRARY_VALUES(...) ::boost::advanced_enum::supplies::arbitrary<__VA_ARGS__>::values
//uncomment to test 

//Action ultimately expands to this:
namespace example{
	namespace {
		namespace _artifacts_Action{
			typedef int UnderlyingT;
			char jump[] = "jump";
			char look[] = "look";
			char move[] = "move";
			enum class index{
				jump,
				look,
				move,
			};
			typedef ::boost::advanced_enum::enum_storage<int, ::boost::advanced_enum::supplies::shiftL1<int>::values>::gen<jump, look, move>::get enum_storage;
		}
	}
	enum class Action : _artifacts_Action::UnderlyingT {
		jump = _artifacts_Action::enum_storage::value_at<static_cast<int>(_artifacts_Action::index::jump)>::value,
		look = _artifacts_Action::enum_storage::value_at<static_cast<int>(_artifacts_Action::index::look)>::value,
		move = _artifacts_Action::enum_storage::value_at<static_cast<int>(_artifacts_Action::index::move)>::value,
	};
	namespace {
		namespace _artifacts_Action{
			typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, Action> Base;
		}
	}
	struct Action_enum : _artifacts_Action::Base {
		Action_enum() : _artifacts_Action::Base(){}
		Action_enum(ValueT v) : _artifacts_Action::Base(v){}
		explicit Action_enum(int v) : _artifacts_Action::Base(v){}
		explicit Action_enum(const std::string& s) : _artifacts_Action::Base(s){}
	};

		BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(Action2)											
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING, jump, look, move)		
		BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(::boost::advanced_enum::supplies::increment<int>::values, jump, look, move)
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_INDEX, jump, look, move)
		BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION												
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL_W_NAME(Action2, BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE, jump, look, move)		
		BOOST_ADVANCED_ENUM__END_DEFINITION(Action2)

}