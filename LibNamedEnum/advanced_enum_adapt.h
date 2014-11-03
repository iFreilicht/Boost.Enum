
#pragma once

#ifdef __EDG__
#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1
#endif

#include "empty_argument.h"
#include "advanced_enum_base.h"
#include "enum_storage2.hpp"
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

#pragma region NAME_COMMA

#define BOOST_ADVANCED_ENUM__NAME_COMMA(valtup) \
	BOOST_PP_TUPLE_ELEM(0, valtup),	\

#pragma endregion

#pragma region DEFINE_ENUM_VALUE

#define BOOST_ADVANCED_ENUM__GET_SUPPLY_VALUE(enum_name, valtup) \
	::boost::advanced_enum::supplies::at<\
		BOOST_PP_CAT(_artifacts0_, enum_name)::UnderlyingT, \
		BOOST_PP_CAT(_artifacts0_, enum_name)::supply::values, \
		static_cast<unsigned int>(BOOST_PP_CAT(_artifacts0_, enum_name)::index::BOOST_PP_TUPLE_ELEM(0, valtup))\
	>::value

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_1(enum_name, deftup) \
	BOOST_ADVANCED_ENUM__GET_SUPPLY_VALUE(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_0(enum_name, deftup) \
	BOOST_PP_TUPLE_ELEM(0, BOOST_PP_TUPLE_ELEM(1, deftup))

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_1(enum_name, deftup) \
	BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_1(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_2(enum_name, deftup) \
	BOOST_PP_CAT( \
		BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_EMPTY_, \
		BOOST_ADVANCED_ENUM_EMPTY_ARG(BOOST_PP_TUPLE_ELEM(1, deftup)) \
	)(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_3(enum_name, deftup) \
	BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_2(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE(enum_name, deftup) \
	BOOST_PP_CAT( \
		BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE_, \
		BOOST_PP_TUPLE_SIZE(deftup) \
	)(enum_name, deftup)

#define BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(enum_name, deftup) \
	BOOST_PP_TUPLE_ELEM(0, deftup) = BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE(enum_name, deftup),


#pragma endregion

#pragma region DEFINE_NAME_VALUE_PAIR

//takes tuple like (name), (name, value) or (name, value, string)
#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(deftup) \
	BOOST_PP_CAT( \
		BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_, \
		BOOST_PP_TUPLE_SIZE(deftup) \
	)(deftup)

#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3(deftup) \
    struct BOOST_PP_TUPLE_ELEM(0, deftup){ \
        static const std::string name; \
        static const EnumT value = EnumT::BOOST_PP_TUPLE_ELEM(0, deftup); \
			    };  \
    const std::string BOOST_PP_TUPLE_ELEM(0, deftup)::name = BOOST_PP_TUPLE_ELEM(2, deftup);


#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(valtup)                          \
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3((BOOST_PP_TUPLE_ELEM(0, valtup), _, BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, valtup))))

//The given value is ignored, we are interested in the actual one
#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_2(deftup) \
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(deftup)

#pragma endregion

#pragma region ADAPT_NAME_VALUE_PAIR

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_1(adatup) \
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(adatup)

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_2(adatup) \
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3( \
		( \
			BOOST_PP_TUPLE_ELEM(0, adatup), \
			_, \
			BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, adatup))\
		)\
	)

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR(adatup) \
	BOOST_PP_CAT( \
		BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_, \
		BOOST_PP_TUPLE_SIZE(adatup) \
	)(adatup)


#pragma endregion


#define BOOST_ADVANCED_ENUM__BEGIN_ADAPTATION(enum_name, underlying)	\
namespace {													\
	namespace BOOST_PP_CAT(_artifacts_,enum_name){			\
		typedef enum_name EnumT;							\
		typedef underlying UnderlyingT;						\

#define BOOST_ADVANCED_ENUM__BEGIN_STORAGE_ADAPTATION	\
		typedef ::boost::advanced_enum::enum_storage2<UnderlyingT>::gen<	\

#define BOOST_ADVANCED_ENUM__ADAPT_STORAGE_VALUE(valtup) \
			BOOST_PP_TUPLE_ELEM(0, valtup),				\

#define BOOST_ADVANCED_ENUM__END_ADAPTATION(enum_name)	\
			void>::get enum_storage;	\
		typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base;	\
		}	\
}			\
struct BOOST_PP_CAT(enum_name, _enum) : BOOST_PP_CAT(_artifacts_, enum_name)::Base {	\
	BOOST_PP_CAT(enum_name, _enum)() : BOOST_PP_CAT(_artifacts_, enum_name)::Base(){}			\
	BOOST_PP_CAT(enum_name, _enum)(ValueT v) : BOOST_PP_CAT(_artifacts_, enum_name)::Base(v){}	\
	explicit BOOST_PP_CAT(enum_name, _enum)(UnderlyingT v) : BOOST_PP_CAT(_artifacts_, enum_name)::Base(v){}	\
	explicit BOOST_PP_CAT(enum_name, _enum)(const std::string& s) : BOOST_PP_CAT(_artifacts_, enum_name)::Base(s){}	\
};																									\
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
}																							\


#define BOOST_ADVANCED_ENUM_ADAPT(enum_name, underlying, ...)										\
	BOOST_ADVANCED_ENUM__BEGIN_ADAPTATION(enum_name, underlying)									\
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR, __VA_ARGS__)		\
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_ADAPTATION													\
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__ADAPT_STORAGE_VALUE, __VA_ARGS__)		\
	BOOST_ADVANCED_ENUM__END_ADAPTATION(enum_name)													\

namespace example{
#define FIVE (five, (5))
#define SIX (six)
#define SEVEN (seven, _, "Sieben")
#define TWENTY (twenty, (20), "Zwanzig")


	namespace {
		namespace _artifacts0_AdaptLater{
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

	const int thing = BOOST_ADVANCED_ENUM__DETERMINE_ENUM_VALUE(AdaptLater, TWENTY);

	enum class AdaptLater{
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, FIVE)
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, SIX)
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, SEVEN)
		BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(AdaptLater, TWENTY)
	};

	namespace {
		namespace _artifacts1_AdaptLater{
			typedef AdaptLater EnumT;
			typedef int UnderlyingT;
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(FIVE)
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SIX)
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(SEVEN)
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(TWENTY)
			typedef ::boost::advanced_enum::enum_storage2<UnderlyingT>::gen<
				BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SIX)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SEVEN)
				BOOST_ADVANCED_ENUM__NAME_COMMA(TWENTY)
			void>::get enum_storage;
			typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base;
		}
	}
	struct AdaptLater_enum : _artifacts1_AdaptLater::Base {
		AdaptLater_enum() : _artifacts1_AdaptLater::Base(){}
		AdaptLater_enum(ValueT v) : _artifacts1_AdaptLater::Base(v){}
		explicit AdaptLater_enum(UnderlyingT v) : _artifacts1_AdaptLater::Base(v){}
		explicit AdaptLater_enum(const std::string& s) : _artifacts1_AdaptLater::Base(s){}
	};
	std::istream& operator >>(std::istream& lhs, AdaptLater& rhs){
		std::string s;
		lhs >> s;
		try{
			rhs = static_cast<AdaptLater_enum>(s);
		}
		catch (const std::invalid_argument&){}
		return lhs;
	}
	inline std::ostream& operator <<(std::ostream& lhs, AdaptLater rhs){
		return lhs << static_cast<std::string>((AdaptLater_enum) rhs);
	}


	AdaptLater val = AdaptLater::six;
	AdaptLater_enum e = val;

	enum class AdaptLater2{
		five = 5,
		six,
		twenty = 20
	};

	BOOST_ADVANCED_ENUM__BEGIN_ADAPTATION(AdaptLater2, int)									
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR, (five), (six), (twenty))
	BOOST_ADVANCED_ENUM__BEGIN_STORAGE_ADAPTATION
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__ADAPT_STORAGE_VALUE, (five), (six), (twenty))
	BOOST_ADVANCED_ENUM__END_ADAPTATION(AdaptLater2)

	AdaptLater2 val2 = AdaptLater2::six;
	AdaptLater2_enum e2 = val2;
}