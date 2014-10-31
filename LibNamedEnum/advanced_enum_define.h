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

#define BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE(name)										\
			name = enum_storage::													\
				value_at<static_cast<enum_storage::SizeT>(index::name)>::value,		\

#define BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)			\
		};																\
		typedef ::boost::advanced_enum::advanced_enum_base			\
			<enum_storage, Values> Base;					\
	}																\
}																	\
struct  enum_name : BOOST_PP_CAT(_artifacts_,enum_name)::Base {			\

#define BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(name)						\
	static const ValueT name = ValueT::name;							\

#define BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)											\
	enum_name() : BOOST_PP_CAT(_artifacts_,enum_name)::Base(){}									\
	enum_name(ValueT v) : BOOST_PP_CAT(_artifacts_,enum_name)::Base(v){}						\
	explicit enum_name(UnderlyingT v) : BOOST_PP_CAT(_artifacts_,enum_name)::Base(v){}			\
	explicit enum_name(const std::string& s) : BOOST_PP_CAT(_artifacts_,enum_name)::Base(s){}	\
};																								\


///Forward declare an advanced_enum
#define BOOST_ADVANCED_ENUM_FWD_DECLARE(enum_name) \
struct enum_name

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
		BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)										\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE, __VA_ARGS__)		\
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
			char jump[] = "jump";
			char look[] = "look";
			char move[] = "move";
			enum class index{
				jump,
				look,
				move,
			};
			typedef ::boost::advanced_enum::enum_storage<int, ::boost::advanced_enum::supplies::shiftL1<int>::values>::gen<jump, look, move>::get enum_storage;
			enum class Values{
				jump = enum_storage::value_at<static_cast<int>(index::jump)>::value,
				look = enum_storage::value_at<static_cast<int>(index::look)>::value,
				move = enum_storage::value_at<static_cast<int>(index::move)>::value,
			};
			typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, Values> Base;
		}
	}
	struct Action : _artifacts_Action::Base {
		static const ValueT jump = ValueT::jump;
		static const ValueT look = ValueT::look;
		static const ValueT move = ValueT::move;
		Action() : _artifacts_Action::Base(){}
		Action(ValueT v) : _artifacts_Action::Base(v){}
		explicit Action(int v) : _artifacts_Action::Base(v){}
		explicit Action(const std::string& s) : _artifacts_Action::Base(s){}
	};

		BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(Action2)											
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING, jump, look, move)		
		BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(::boost::advanced_enum::supplies::increment<int>::values, jump, look, move)
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_INDEX, jump, look, move)
		BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION												
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE, jump, look, move)		
		BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINITION(Action2)							
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE, jump, look, move)
		BOOST_ADVANCED_ENUM__END_DEFINITION(Action2)

}