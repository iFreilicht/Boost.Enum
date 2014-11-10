#pragma once

#include "macros/define_name_value_pair.h"
#include "macros/define_enum_value.h"
#include "macros/name_comma.h"
#include "macros/artifacts_namespace.h"
#include "macros/derive_enum_base.h"
#include "macros/overload_stream_operators.h"
#include "macros/apply_to_all.h"

#include "advanced_enum_base.h"
#include "enum_storage.hpp"


#define BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name, supply_)			\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)						\
		typedef int UnderlyingT;											\
		typedef supply_ supply;												\
		enum class index : unsigned int{									\

#define BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(enum_name)				\
		};																	\
		enum class EnumT{													\


#define BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(enum_name)			\
		};																	\

#define BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(enum_name)			\
		typedef ::boost::advanced_enum::enum_storage<UnderlyingT>::gen <	\

#define BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)						\
		void > ::get enum_storage;											\
		typedef ::boost::advanced_enum::									\
			advanced_enum_base <enum_storage, EnumT> Base;					\
		BOOST_ADVANCED_ENUM__DERIVE_ENUM_BASE								\
		BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS						\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS									\
	typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT enum_name;		\


#define BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, supply, seq)			\
	BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name, supply)				\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)									\
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(enum_name)					\
	BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(seq)								\
	BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(enum_name)				\
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(seq)						\
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(enum_name)				\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)									\
	BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)


#define BOOST_ADVANCED_ENUM_FWD_DECLARE(enum_name)							\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)						\
	enum class EnumT;														\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS									\
	typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT enum_name;		\

#define BOOST_ADVANCED_ENUM_DEFINE(enum_name, seq) \
	BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::advanced_enum::supplies::increment<int>, seq)


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
			enum class EnumT{
				BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(FIVE)
				BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(SIX)
				BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(SEVEN)
				BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(TWENTY)
			};
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(FIVE)
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SIX)
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SEVEN)
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(TWENTY)
			typedef ::boost::advanced_enum::enum_storage<UnderlyingT>::gen <
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
			std::istream& operator >>(std::istream& lhs, EnumT& rhs){
				std::string s;
				lhs >> s;
				try{
					rhs = static_cast<advanced_enum>(s);
				}
				catch (const std::invalid_argument&){}
				return lhs;
			}
			inline std::ostream& operator <<(std::ostream& lhs, EnumT rhs){
				return lhs << static_cast<std::string>((advanced_enum)rhs);
			}
		}
	}
	typedef _artifacts_AdaptLater::EnumT AdaptLater;
	/*std::istream& operator >>(std::istream& lhs, AdaptLater& rhs){
		std::string s;
		lhs >> s;
		try{
			rhs = (AdaptLater)static_cast<int>(static_cast<_artifacts_AdaptLater::advanced_enum>(s));
		}
		catch (const std::invalid_argument&){}
		return lhs;
	}
	inline std::ostream& operator <<(std::ostream& lhs, AdaptLater rhs){
		return lhs << static_cast<std::string>((_artifacts_AdaptLater::advanced_enum)(int)rhs);
	}*/


	BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(Adapt2, ::boost::advanced_enum::supplies::increment<int>) 
	BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(Adapt2) 
	BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(Adapt2) 
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(Adapt2) 
	BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__END_DEFINITION(Adapt2)
}