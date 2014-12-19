#pragma once

#include "config.hpp"
#include <boost/preprocessor/tuple/rem.hpp>
#include "macros/define_name_value_pair.h"
#include "macros/define_enum_value.h"
#include "macros/name_comma.h"
#include "macros/insert_enum_value.h"
#include "macros/artifacts_namespace.h"
#include "macros/derive_enum_base.h"
#include "macros/overload_stream_operators.h"
#include "macros/apply_to_all.h"

#include "advanced_enum_base.h"
#include "enum_storage.hpp"
#include "options.h"
#include "function_implementations.h"

#define BOOST_ADVANCED_ENUM_DEFINE_I(enum_name, options_)			\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)						\
		typedef BOOST_PP_CAT(BOOST_PP_REM, options_) options;				\
		typedef options::Supply supply;										\
		typedef options::UnderlyingT UnderlyingT;							\
		enum class index : std::make_unsigned<UnderlyingT>::type{			\

#define BOOST_ADVANCED_ENUM_DEFINE_II(enum_name)				\
		};																	\
		enum class EnumT : UnderlyingT{										\


#define BOOST_ADVANCED_ENUM_DEFINE_III(enum_name)			\
		};																	\

#define BOOST_ADVANCED_ENUM_DEFINE_IV(enum_name)			\
		typedef ::boost::advanced_enum::									\
			enum_storage<options>::gen <								\

#define BOOST_ADVANCED_ENUM_DEFINE_V(enum_name)								\
		void > ::get enum_storage;											\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS									\
	class enum_name :														\
		public ::boost::advanced_enum::function_impl::OrderingImpl<			\
			BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT,				\
			BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::options::UnderlyingT,\
			BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::options::no_ordering	\
				>,															\
		public ::boost::advanced_enum::function_impl::BitwiseImpl<			\
			enum_name,														\
			BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT,				\
			BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::options::UnderlyingT,\
			BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::options::is_flag		\
		>																	\
	{																		\
		typedef enum_name OwnT;												\
	public:																	\
		typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::options options;	\
		typedef options::Supply supply;										\
		typedef options::UnderlyingT UnderlyingT;							\
		typedef options::StringT StringT;									\
		typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::enum_storage EnumStorage;	\
		typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT EnumT;					\
	private:																			\
		EnumT value_;														\
		UnderlyingT get_val_() const override								\
			{ return static_cast<UnderlyingT>(value_); }					\
		void set_val_(UnderlyingT val) override								\
			{ value_ = static_cast<EnumT>(val); }							\
		enum_name* this_() override { return this; }						\
		typedef ::boost::advanced_enum::function_impl::UnderlyingToEnumImpl	\
			<enum_name, options::arbitrary> UnderlyingToEnumImpl;			\
	public:																	\

#define BOOST_ADVANCED_ENUM_DEFINE_VI(enum_name)							\
		enum_name(){}														\
		enum_name(const enum_name& other) : value_(other.value_){}			\
		enum_name(const EnumT val) : value_(val){}							\
		operator EnumT() const { return value_; }							\
		enum_name& operator =(const enum_name& rhs)							\
			{ value_ = rhs.value_; return *this; }							\
		enum_name& operator =(EnumT rhs){ value_ = rhs; return *this; }		\
																			\
		explicit enum_name(UnderlyingT val) :								\
			value_(UnderlyingToEnumImpl::f(val)){}							\
		explicit enum_name(const StringT& str) :							\
			value_(UnderlyingToEnumImpl::f(EnumStorage::stoe(str))) {}		\
		explicit operator UnderlyingT() const								\
			{ return static_cast<UnderlyingT>(value_); }					\
		explicit operator StringT() const									\
			{ return EnumStorage::etos(static_cast<UnderlyingT>(value_)); }	\
																			\
		static bool has_value(UnderlyingT val)								\
			{ return EnumStorage::has_value(val); }							\
																			\
		friend bool operator ==(const enum_name&, const enum_name&);		\
																			\
	};																		\
																			\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	operator&(ValueT lhs, ValueT rhs){										\
		return enum_name(lhs) & enum_name(rhs);								\
	}																		\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	operator|(ValueT lhs, ValueT rhs){										\
		return enum_name(lhs) | enum_name(rhs);								\
	}																		\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	operator^(ValueT lhs, ValueT rhs){										\
		return enum_name(lhs) ^ enum_name(rhs);								\
	}																		\
	template<typename ValueT>												\
	typename std::enable_if<std::is_convertible<ValueT, enum_name>::value &&\
		!std::is_same<ValueT, enum_name>::value, enum_name>::type			\
	operator~(ValueT rhs){													\
		return ~enum_name(rhs);												\
	}																		\
																			\
	bool operator ==(const enum_name& lhs, const enum_name& rhs)			\
		{ return lhs.value_ == rhs.value_; }								\
	bool operator !=(const enum_name& lhs, const enum_name& rhs)			\
		{ return !(lhs == rhs); }											\
																			\
	std::istream& operator>>(std::istream& is, enum_name& nt){				\
		std::string str;													\
		is >> str;															\
		try{																\
			nt = static_cast<enum_name>(str);								\
		}																	\
		catch(const std::invalid_argument&){}								\
		return is;															\
	}																		\
																			\
	std::ostream& operator<<(std::ostream& os, const enum_name& nt){		\
		return os << static_cast<std::string>(nt);							\
	}																		\
																			\

	


#if defined BOOST_ADVANCED_ENUM_DISABLE_INTELLISENSE_WORKAROUND || !defined __INTELLISENSE__
#define BOOST_ADVANCED_ENUM_DEFINE_W_OPTIONS(enum_name, options, seq)		\
	BOOST_ADVANCED_ENUM_DEFINE_I(enum_name, options)						\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)									\
	BOOST_ADVANCED_ENUM_DEFINE_II(enum_name)								\
	BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(seq)								\
	BOOST_ADVANCED_ENUM_DEFINE_III(enum_name)								\
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(seq)						\
	BOOST_ADVANCED_ENUM_DEFINE_IV(enum_name)								\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)									\
	BOOST_ADVANCED_ENUM_DEFINE_V(enum_name)									\
	BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(seq)								\
	BOOST_ADVANCED_ENUM_DEFINE_VI(enum_name)								\

#else
//WARNING! IntelliSense will not display the correct values!
#define BOOST_ADVANCED_ENUM_DEFINE_W_OPTIONS(enum_name, options, seq)		\
	BOOST_ADVANCED_ENUM_DEFINE_I(enum_name, options)						\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)									\
	BOOST_ADVANCED_ENUM_DEFINE_II(enum_name)								\
	BOOST_ADVANCED_ENUM__NAME_COMMA(seq)								\
	BOOST_ADVANCED_ENUM_DEFINE_III(enum_name)								\
	BOOST_ADVANCED_ENUM_DEFINE_IV(enum_name)								\
	BOOST_ADVANCED_ENUM_DEFINE_V(enum_name)									\
	BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(seq)								\
	BOOST_ADVANCED_ENUM_DEFINE_VI(enum_name)								\

#endif


#define BOOST_ADVANCED_ENUM_FWD_DECLARE(enum_name, underlyingT)				\
	BOOST_ADVANCED_ENUM__ENTER_ARTIFACTS_NS(enum_name)						\
	enum class EnumT : underlyingT;											\
	BOOST_ADVANCED_ENUM__EXIT_ARTIFACTS_NS									\
	typedef BOOST_ADVANCED_ENUM__ARTIFACTS(enum_name)::EnumT enum_name;		\

#define BOOST_ADVANCED_ENUM_DEFINE(enum_name, underlyingT, seq) \
	BOOST_ADVANCED_ENUM_DEFINE_W_OPTIONS(enum_name,				\
		(::boost::advanced_enum::Options<>), seq)






namespace example{
#define FIVE (five, (5))
#define SIX (six)
#define SEVEN (seven, _, "Sieben")
#define TWENTY (twenty, (20), "Zwanzig")


	namespace {
		namespace _artifacts_NewTest{
			typedef ::boost::advanced_enum::Options<0> options;
			typedef options::Supply supply;
			typedef options::UnderlyingT UnderlyingT;
			enum class index : std::make_unsigned<UnderlyingT>::type{
				BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SIX)
				BOOST_ADVANCED_ENUM__NAME_COMMA(SEVEN)
				BOOST_ADVANCED_ENUM__NAME_COMMA(TWENTY)
			};
			enum class EnumT : UnderlyingT {
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
		}
	}

	
	class NewTest : 
		public ::boost::advanced_enum::function_impl::OrderingImpl<
			_artifacts_NewTest::EnumT, 
			_artifacts_NewTest::options::UnderlyingT, 
			_artifacts_NewTest::options::no_ordering
		>,
		public ::boost::advanced_enum::function_impl::BitwiseImpl<
			NewTest,
			_artifacts_NewTest::EnumT,
			_artifacts_NewTest::options::UnderlyingT,
			_artifacts_NewTest::options::is_flag
		>
	{
		typedef NewTest OwnT;
	public:
		typedef _artifacts_NewTest::options options;
		typedef options::Supply supply;
		typedef options::UnderlyingT UnderlyingT;
		typedef options::StringT StringT;
		typedef _artifacts_NewTest::enum_storage EnumStorage;
		typedef _artifacts_NewTest::EnumT EnumT;
	private:
		EnumT value_;

		UnderlyingT get_val_() const override{ return static_cast<UnderlyingT>(value_); }
		void set_val_(UnderlyingT val) override{ value_ = static_cast<EnumT>(val); }
		NewTest* this_() override{ return this; }

		typedef ::boost::advanced_enum::function_impl::UnderlyingToEnumImpl<NewTest, options::arbitrary> UnderlyingToEnumImpl;
	public:
		BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(FIVE)
		BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(SIX)
		BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(SEVEN)
		BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(TWENTY)

		NewTest(){}
		NewTest(const NewTest& other) : value_(other.value_){}
		NewTest(const EnumT val) : value_(val){}
		operator EnumT() const { return value_; }
		NewTest& operator =(const NewTest& rhs){ value_ = rhs.value_; return *this; }
		NewTest& operator =(EnumT rhs){ value_ = rhs; return *this; }

		explicit NewTest(UnderlyingT val) : value_(UnderlyingToEnumImpl::f(val)){}
		explicit NewTest(const StringT& str) : value_(UnderlyingToEnumImpl::f(EnumStorage::stoe(str))) {}
		explicit operator UnderlyingT() const{ return static_cast<UnderlyingT>(value_); }
		explicit operator StringT() const{ return EnumStorage::etos(static_cast<UnderlyingT>(value_)); }

		static bool has_value(UnderlyingT val){ return EnumStorage::has_value(val); }

		friend bool operator ==(const NewTest&, const NewTest&);
	};

	bool operator ==(const NewTest& lhs, const NewTest& rhs){ return lhs.value_ == rhs.value_; }
	bool operator !=(const NewTest& lhs, const NewTest& rhs){ return !(lhs == rhs); }

#ifdef BOOST_NO_CONSTEXPR
	//overload operators for ValueT <op> ValueT calls
	template<typename ValueT>
	typename std::enable_if<std::is_convertible<ValueT, NewTest>::value && !std::is_same<ValueT, NewTest>::value, NewTest>::type
		operator&(ValueT lhs, ValueT rhs){
		return NewTest(lhs) & NewTest(rhs);
	}
	template<typename ValueT>
	typename std::enable_if<std::is_convertible<ValueT, NewTest>::value && !std::is_same<ValueT, NewTest>::value, NewTest>::type
		operator|(ValueT lhs, ValueT rhs){
		return NewTest(lhs) | NewTest(rhs);
	}
	template<typename ValueT>
	typename std::enable_if<std::is_convertible<ValueT, NewTest>::value && !std::is_same<ValueT, NewTest>::value, NewTest>::type
		operator^(ValueT lhs, ValueT rhs){
		return NewTest(lhs) ^ NewTest(rhs);
	}
	template<typename ValueT>
	typename std::enable_if<std::is_convertible<ValueT, NewTest>::value && !std::is_same<ValueT, NewTest>::value, NewTest>::type
		operator~(ValueT rhs){
		return ~NewTest(rhs);
	}
#endif

	std::istream& operator>>(std::istream& is, NewTest& nt){
		std::string str;
		is >> str;
		try{
			nt = static_cast<NewTest>(str);
		}
		catch(const std::invalid_argument&){}
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const NewTest& nt){
		return os << static_cast<std::string>(nt);
	}

	BOOST_ADVANCED_ENUM_DEFINE_I(NewTest2, (::boost::advanced_enum::Options<>))
	BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM_DEFINE_II(NewTest2)
	BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM_DEFINE_III(NewTest2)
	BOOST_ADVANCED_ENUM__DEFINE_NAME_VALUE_PAIR(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM_DEFINE_IV(NewTest2)
	BOOST_ADVANCED_ENUM__NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM_DEFINE_V(NewTest2)
	BOOST_ADVANCED_ENUM__INSERT_ENUM_VALUE(FIVE SIX SEVEN TWENTY)
	BOOST_ADVANCED_ENUM_DEFINE_VI(NewTest2)
}