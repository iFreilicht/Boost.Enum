
#pragma once

#include "advanced_enum_base.h"
#include "enum_storage2.hpp"
#ifdef __EDG__
#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1
#endif
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple.hpp>
#include <string>


#pragma region DEFINE_NAME_VALUE_PAIR

//takes tuple like (name), (name, value) or (name, value, string)
#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(tuple) BOOST_PP_CAT(BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_, BOOST_PP_TUPLE_SIZE(tuple))(tuple)

#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(tuple)                          \
    struct BOOST_PP_TUPLE_ELEM(0, tuple){ \
        static const std::string name; \
        static const EnumT value = EnumT::BOOST_PP_TUPLE_ELEM(0, tuple); \
    };  \
    const std::string BOOST_PP_TUPLE_ELEM(0, tuple)::name = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, tuple));

#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_2(tuple) \
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(tuple)

#define BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3(tuple) \
    struct BOOST_PP_TUPLE_ELEM(0, tuple){ \
        static const std::string name; \
        static const EnumT value = EnumT::BOOST_PP_TUPLE_ELEM(0, tuple); \
    };  \
    const std::string BOOST_PP_TUPLE_ELEM(0, tuple)::name = BOOST_PP_TUPLE_ELEM(2, tuple);

#pragma endregion


#define BOOST_ADVANCED_ENUM__GET_SUPPLY_VALUE(enum_name,supply,name) \
	::boost::advanced_enum::supplies::at<supply::values, \
		static_cast<unsigned int>(::boost::advanced_enum::artifacts::BOOST_PP_CAT(enum_name,_)::index::name)>::value



#define BOOST_ADVANCED_ENUM__BEGIN_ADAPTATION(enum_name, underlying)	\
namespace {													\
	namespace BOOST_PP_CAT(_artifacts_,enum_name){			\
		typedef enum_name EnumT;							\
		typedef underlying UnderlyingT;						\

//the tuple should have the form (name) or (name, string)
#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR(tuple) BOOST_PP_CAT(BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_, BOOST_PP_TUPLE_SIZE(tuple))(tuple)

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_1(tuple) BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_1(tuple)

#define BOOST_ADVANCED_ENUM__ADAPT_NAME_VALUE_PAIR_2(tuple) BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR_3((BOOST_PP_TUPLE_ELEM(0, tuple), _, BOOST_PP_TUPLE_ELEM(2, tuple)))

#define BOOST_ADVANCED_ENUM__BEGIN_STORAGE_ADAPTATION	\
		typedef ::boost::advanced_enum::enum_storage2<UnderlyingT>::gen<	\

#define BOOST_ADVANCED_ENUM__ADAPT_STORAGE_VALUE(tuple) \
			BOOST_PP_TUPLE_ELEM(0, tuple),				\

#define BOOST_ADVANCED_ENUM__BEGIN_ENUM_ADAPTATION(enum_name)		\
		void>::get enum_storage;	\
		typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base;	\
	}	\
}			\
struct BOOST_PP_CAT(enum_name, _enum) : BOOST_PP_CAT(_artifacts_, enum_name)::Base {	\

#define BOOST_ADVANCED_ENUM__ADAPT_ENUM_VALUE(tuple)	\
	static const ValueT BOOST_PP_TUPLE_ELEM(0, tuple) = ValueT::BOOST_PP_TUPLE_ELEM(0, tuple);

#define BOOST_ADVANCED_ENUM__END_ADAPTATION(enum_name)	\
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
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_ADAPTATION(enum_name)											\
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__ADAPT_ENUM_VALUE, __VA_ARGS__)			\
	BOOST_ADVANCED_ENUM__END_ADAPTATION(enum_name)													\

namespace example{
	enum class AdaptLater{
		five = 5,
		six,
		twenty = 20
	};

	namespace {
		namespace _artifacts_AdaptLater{
			typedef AdaptLater EnumT;
			typedef int UnderlyingT;
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR((five));
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR((six));
			BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR((twenty));
			typedef ::boost::advanced_enum::enum_storage2<UnderlyingT>::gen<five, six, twenty>::get enum_storage;
			typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, EnumT> Base;
		}
	}
	struct AdaptLater_enum : _artifacts_AdaptLater::Base {
		static const ValueT five = ValueT::five;
		static const ValueT six = ValueT::six;
		static const ValueT twenty = ValueT::twenty;
		AdaptLater_enum() : _artifacts_AdaptLater::Base(){}
		AdaptLater_enum(ValueT v) : _artifacts_AdaptLater::Base(v){}
		explicit AdaptLater_enum(UnderlyingT v) : _artifacts_AdaptLater::Base(v){}
		explicit AdaptLater_enum(const std::string& s) : _artifacts_AdaptLater::Base(s){}
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
	BOOST_ADVANCED_ENUM__BEGIN_ENUM_ADAPTATION(AdaptLater2)
	BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__ADAPT_ENUM_VALUE, (five), (six), (twenty))
	BOOST_ADVANCED_ENUM__END_ADAPTATION(AdaptLater2)

	AdaptLater2 val2 = AdaptLater2::six;
	AdaptLater2_enum e2 = val2;
}