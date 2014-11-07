
#pragma once

#ifdef __EDG__
#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1
#endif

#include "macros/empty_argument.h"
#include "macros/name_comma.h"
#include "macros/adapt_name_value_pair.h"
#include "macros/define_enum_value.h"
#include "macros/artifacts_namespace.h"
#include "macros/derive_enum_base.h"
#include "macros/overload_stream_operators.h"
#include "macros/apply_to_all.h"

#include "advanced_enum_base.h"
#include "enum_storage.hpp"
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple.hpp>
#include <string>

//-----------------------------
//IMPORTANT!
//deftup is a Boost.PP tuple of one of the following forms:
// (name),
// (name, _)
// (name, (value)) 
// (name, (value), string)
// (name, _, string)
//
//adatup is a Boost.PP tuple of one of the following forms:
// (name),
// (name, string)
//
//valtup is compatible with both defintions, i.e. the function only uses the first argument
//------------------------------


#define BOOST_ADVANCED_ENUM__BEGIN_ADAPTATION(enum_name, underlying)								\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)												\
		typedef enum_name EnumT;																	\
		typedef underlying UnderlyingT;																\

#define BOOST_ADVANCED_ENUM__BEGIN_STORAGE_ADAPTATION												\
		typedef ::boost::advanced_enum::enum_storage<UnderlyingT>::gen<							\

#define BOOST_ADVANCED_ENUM__END_ADAPTATION(enum_name)												\
		void>::get enum_storage;																	\
		typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base;				\
		BOOST_ADVANCED_ENUM__DERIVE_ENUM_BASE														\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS															\
	BOOST_ADVANCED_ENUM__OVERLOAD_STREAM_OPERATORS_W_NAME(enum_name)									\

#define BOOST_ADVANCED_ENUM_ADAPT(enum_name, underlying, seq)										\
	BOOST_ADVANCED_ENUM__BEGIN_ADAPTATION(enum_name, underlying)									\
	BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR(seq)													\
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_ADAPTATION													\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)															\
	BOOST_ADVANCED_ENUM__END_ADAPTATION(enum_name)													\

namespace example{
//#define FIVE (five, (5))
//#define SIX (six)
//#define SEVEN (seven, _, "Sieben")
//#define TWENTY (twenty, (20), "Zwanzig")
//
//
//	namespace {
//		namespace _artifacts_AdaptLater{
//			typedef int UnderlyingT;
//			typedef ::boost::advanced_enum::supplies::shiftL1<UnderlyingT> supply;
//			enum class index : unsigned int{
//				BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE)
//				BOOST_ADVANCED_ENUM__NAME_COMMA(SIX)
//				BOOST_ADVANCED_ENUM__NAME_COMMA(SEVEN)
//				BOOST_ADVANCED_ENUM__NAME_COMMA(TWENTY)
//			};
//		}
//	}
//
//	enum class AdaptLater{
//		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, FIVE)
//		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, SIX)
//		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, SEVEN)
//		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, TWENTY)
//	};
//
//	namespace {
//		namespace _artifacts_AdaptLater{
//			typedef AdaptLater EnumT;
//			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(FIVE)
//			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SIX)
//			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SEVEN)
//			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(TWENTY)
//			typedef ::boost::advanced_enum::enum_storage<UnderlyingT>::gen<
//				BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE)
//				BOOST_ADVANCED_ENUM__NAME_COMMA(SIX)
//				BOOST_ADVANCED_ENUM__NAME_COMMA(SEVEN)
//				BOOST_ADVANCED_ENUM__NAME_COMMA(TWENTY)
//			void>::get enum_storage;
//			typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base;
//		}
//	}
//	struct AdaptLater_enum : _artifacts_AdaptLater::Base {
//		AdaptLater_enum() : _artifacts_AdaptLater::Base(){}
//		AdaptLater_enum(ValueT v) : _artifacts_AdaptLater::Base(v){}
//		explicit AdaptLater_enum(UnderlyingT v) : _artifacts_AdaptLater::Base(v){}
//		explicit AdaptLater_enum(const std::string& s) : _artifacts_AdaptLater::Base(s){}
//	};
//	std::istream& operator >>(std::istream& lhs, AdaptLater& rhs){
//		std::string s;
//		lhs >> s;
//		try{
//			rhs = static_cast<AdaptLater_enum>(s);
//		}
//		catch (const std::invalid_argument&){}
//		return lhs;
//	}
//	inline std::ostream& operator <<(std::ostream& lhs, AdaptLater rhs){
//		return lhs << static_cast<std::string>((AdaptLater_enum) rhs);
//	}
//
//
//	AdaptLater val = AdaptLater::six;
//	AdaptLater_enum e = val;

	enum class AdaptLater2{
		five = 5,
		six,
		twenty = 20
	};

	BOOST_ADVANCED_ENUM__BEGIN_ADAPTATION(AdaptLater2, int)									
	BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR((five)(six, "Sechs")(twenty))
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_ADAPTATION
	BOOST_ADVANCED_ENUM__NAME_COMMA((five)(six, "Sechs")(twenty))
	BOOST_ADVANCED_ENUM__END_ADAPTATION(AdaptLater2)

	AdaptLater2 val2 = AdaptLater2::six;
}