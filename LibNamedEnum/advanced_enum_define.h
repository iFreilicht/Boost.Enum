#pragma once

#include "macros/define_name_value_pair.h"
#include "macros/define_enum_value.h"
#include "macros/name_comma.h"
#include "macros/artifacts_namespace.h"
#include "macros/derive_enum_base.h"
#include "macros/overload_stream_operators.h"

#include "advanced_enum_base.h"
#include "enum_storage2.hpp"


#define BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name, supply_) \
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name) \
		typedef int UnderlyingT;							\
		typedef supply_ supply;							\
		enum class index : unsigned int{				\

#define BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(enum_name) \
		};															\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS						\
	enum class enum_name{										\


#define BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(enum_name) \
	};																\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name) \
		typedef enum_name EnumT;						\

#define BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(enum_name) \
		typedef ::boost::advanced_enum::enum_storage2<UnderlyingT>::gen <

#define BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name) \
		void > ::get enum_storage;							\
		typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base; \
		BOOST_ADVANCED_ENUM__DERIVE_ENUM_BASE							\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS						\
	BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS(enum_name)	\


#define BOOST_ADVANCED_ENUM_DEFINE(enum_name, supply, ...) \
	BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name, supply) \
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__NAME_COMMA, __VA_ARGS__) \
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(enum_name) \
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL_W_NAME(enum_name, BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE, __VA_ARGS__) \
	BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(enum_name) \
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR, __VA_ARGS__) \
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(enum_name) \
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__NAME_COMMA, __VA_ARGS__) \
	BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)


namespace example{
#define FIVE (five, (5))
#define SIX (six)
#define SEVEN (seven, _, "Sieben")
#define TWENTY (twenty, (20), "Zwanzig")


	namespace {
		namespace _artifacts_AdaptLater{
			typedef int UnderlyingT;
			typedef ::boost::advanced_enum::supplies::shiftL1<UnderlyingT> supply;
			enum class index : unsigned int{
				BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SIX)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SEVEN)
				BOOST_ADVANCED_ENUM__NAME_COMMA(TWENTY)
			};
		}
	}

	enum class AdaptLater{
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, FIVE)
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, SIX)
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, SEVEN)
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, TWENTY)
	};

	namespace {
		namespace _artifacts_AdaptLater{
			typedef AdaptLater EnumT;
				BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(FIVE)
				BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SIX)
				BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SEVEN)
				BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(TWENTY)
				typedef ::boost::advanced_enum::enum_storage2<UnderlyingT>::gen <
				BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SIX)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SEVEN)
				BOOST_ADVANCED_ENUM__NAME_COMMA(TWENTY)
				void > ::get enum_storage;
			typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base;
			struct advanced_enum : Base{
					advanced_enum() : Base(){}
					advanced_enum(ValueT v) : Base(v){}
					explicit advanced_enum(UnderlyingT v) : Base(v){}
					explicit advanced_enum(const std::string& s) : Base(s){}
			};

		}
	}
	std::istream& operator >>(std::istream& lhs, AdaptLater& rhs){
		std::string s;
		lhs >> s;
		try{
			rhs = static_cast<_artifacts_AdaptLater::advanced_enum>(s);
		}
		catch (const std::invalid_argument&){}
		return lhs;
	}
	inline std::ostream& operator <<(std::ostream& lhs, AdaptLater rhs){
		return lhs << static_cast<std::string>((_artifacts_AdaptLater::advanced_enum)rhs);
	}


	BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(Adapt2, ::boost::advanced_enum::supplies::increment<int>) 
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__NAME_COMMA, FIVE, SIX, SEVEN, TWENTY) 
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(Adapt2) 
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL_W_NAME(Adapt2, BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE, FIVE, SIX, SEVEN, TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(Adapt2) 
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR, FIVE, SIX, SEVEN, TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(Adapt2) 
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__NAME_COMMA, FIVE, SIX, SEVEN, TWENTY)
	BOOST_ADVANCED_ENUM__END_DEFINITION(Adapt2)
}