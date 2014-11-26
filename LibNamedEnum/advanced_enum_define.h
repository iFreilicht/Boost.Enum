#pragma once

#include "config.hpp"
#include <boost/preprocessor/tuple/rem.hpp>
#include "macros/define_name_value_pair.h"
#include "macros/define_enum_value.h"
#include "macros/name_comma.h"
#include "macros/artifacts_namespace.h"
#include "macros/derive_enum_base.h"
#include "macros/overload_stream_operators.h"
#include "macros/apply_to_all.h"

#include "advanced_enum_base.h"
#include "enum_storage.hpp"
#include "options.h"

#define BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name, ...)			\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)						\
		typedef ::boost::advanced_enum::Options<__VA_ARGS__> options;		\
		typedef options::Supply supply;										\
		typedef options::UnderlyingT UnderlyingT;							\
		enum class index : std::make_unsigned<UnderlyingT>::type{			\

#define BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(enum_name)				\
		};																	\
		enum class EnumT : UnderlyingT{										\


#define BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(enum_name)			\
		};																	\

#define BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(enum_name)			\
		typedef ::boost::advanced_enum::									\
			enum_storage<options>::gen <								\

#define BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)						\
		void > ::get enum_storage;											\
		typedef ::boost::advanced_enum::									\
			advanced_enum_base <enum_storage, EnumT> Base;					\
		BOOST_ADVANCED_ENUM__DERIVE_ENUM_BASE								\
		BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS						\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS									\
	typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT enum_name;		\

#ifndef __INTELLISENSE__
#define BOOST_ADVANCED_ENUM_DEFINE_W_OPTIONS(enum_name, options, seq)		\
	BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(									\
		enum_name,						\
		BOOST_PP_CAT(BOOST_PP_REM, options)\
	)\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)									\
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(enum_name)					\
	BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(seq)								\
	BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(enum_name)				\
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(seq)						\
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(enum_name)				\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)									\
	BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)
#else
//WARNING! IntelliSense will not display the correct values!
#define BOOST_ADVANCED_ENUM_DEFINE_W_OPTIONS(enum_name, underlyingT, seq) \
	enum class enum_name{ \
		BOOST_ADVANCED_ENUM__NAME_COMMA(seq)				\
		};
#endif


#define BOOST_ADVANCED_ENUM_FWD_DECLARE(enum_name)							\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)						\
	enum class EnumT;														\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS									\
	typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT enum_name;		\

#define BOOST_ADVANCED_ENUM_DEFINE(enum_name, underlyingT, seq) \
	BOOST_ADVANCED_ENUM_DEFINE_W_OPTIONS(enum_name, \
		(0, underlyingT), seq)






namespace example{
#define FIVE (five, (5))
#define SIX (six)
#define SEVEN (seven, _, "Sieben")
#define TWENTY (twenty, (20), "Zwanzig")


	namespace {
		namespace _artifacts_AdaptLater{
			typedef ::boost::advanced_enum::Options<0, int> options;
			typedef options::Supply supply;
			typedef options::UnderlyingT UnderlyingT;
			enum class index : std::make_unsigned<UnderlyingT>::type{
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
			typedef ::boost::advanced_enum::enum_storage<options>::gen <
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


	BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(Adapt2, 0, int) 
	BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINTION(Adapt2) 
	BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_NAME_VALUE_DEFINITION(Adapt2) 
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_DEFINITION(Adapt2) 
	BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM__END_DEFINITION(Adapt2)
}