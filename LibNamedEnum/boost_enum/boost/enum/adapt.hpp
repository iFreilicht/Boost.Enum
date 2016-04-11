
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


/*! \file adapt.hpp
	\brief Contains all macros necessary to adapt existing enumerations.

	If you want to use the features of an enumeration that is defined by a library
	or can't change the definition of the `enum` to a DEFINE macro for a different
	reason, the macros of this file allow you to adapt them, leaving the enums 
	themselves unchanged, but still enabling all the advanced features newly defined
	enumerations have.

	All macros defined in this file use a combination of the following three arguments:
	- `enum_name` The name for the new enumeration.
	- `options` \e (optional) An instance of the enum_::adapt_options<> template, 
	enclosed by parenthesis.
	- `seq` A preprocessor sequence where all elements can only be devided by whitespace 
	characters. Each element describes one value of the \c enum that is to be adapted.

	Elements of `seq` define one or two properties of an enumeration value:
	- `value_name` The name of the enumeration value.
	- `string` \e (optional) The string the value should be converted to.

	If `string` isn't specified by the element, the string will be equivalent to the
	stringisation of `value_name`.

	Each element of `seq` can have one of the following forms:
	- `(value_name)`
	- `(value_name, string)`

*/


#ifndef BOOST_ENUM_IG_ADAPT_HPP
#define BOOST_ENUM_IG_ADAPT_HPP

#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/enum/macros/name_comma.hpp>
#include <boost/enum/macros/adapt_name_value_pair.hpp>
#include <boost/enum/macros/define_enum_value.hpp>
#include <boost/enum/macros/artifacts_namespace.hpp>
#include <boost/enum/macros/insert_enum_value.hpp>
#include <boost/enum/macros/overload_binary_operators.hpp>
#include <boost/enum/macros/overload_stream_operators.hpp>
#include <boost/enum/macros/overload_equality_operators.hpp>

#include <boost/enum/storage/function_impl.hpp>
#include <boost/enum/options.hpp>
#include <boost/enum/storage/storage.hpp>
#include <boost/preprocessor/cat.hpp>


#pragma region Implementation
//! \cond AdaptImpl
/////////////////////////////////////////////////////////////////////////////
// All macros in this region are used for implementing and should not be used!
// They are subject to change, just like private member functions.
/////////////////////////////////////////////////////////////////////////////


#define BOOST_ENUM_ADAPT_I(enum_name, options_)								\
	BOOST_ENUM_ENTER_ARTIFACTS_NS(enum_name)								\
		typedef BOOST_PP_CAT(BOOST_PP_REM, options_)						\
			::options<enum_name>::type options;								\
		typedef options::StringT StringT;									\
		typedef options::UnderlyingT UnderlyingT;							\
		typedef enum_name EnumT;											\

#define BOOST_ENUM_ADAPT_II													\
		typedef ::boost::enum_::storage<options>::gen<						\

#define BOOST_ENUM_ADAPT_III(enum_name)										\
		void>::get storage;													\
	BOOST_ENUM_EXIT_ARTIFACTS_NS											\
	class BOOST_PP_CAT(enum_name, _e) :										\
	public ::boost::enum_::function_impl::OrderingImpl<						\
		BOOST_ENUM_ARTIFACTS(enum_name)::EnumT,								\
		BOOST_ENUM_ARTIFACTS(enum_name)::options::UnderlyingT,				\
		BOOST_ENUM_ARTIFACTS(enum_name)::options::no_ordering				\
	>,																		\
	public ::boost::enum_::function_impl::BitwiseImpl<						\
	BOOST_PP_CAT(enum_name, _e),											\
	BOOST_ENUM_ARTIFACTS(enum_name)::EnumT,									\
	BOOST_ENUM_ARTIFACTS(enum_name)::options::UnderlyingT,					\
	BOOST_ENUM_ARTIFACTS(enum_name)::options::is_flag						\
	>																		\
		{																	\
	typedef BOOST_PP_CAT(enum_name, _e) OwnT;								\
	public:																	\
		typedef BOOST_ENUM_ARTIFACTS(enum_name)::options options;			\
		typedef ::boost::enum_::supplies::NoCustomSupply supply;			\
		typedef options::UnderlyingT UnderlyingT;							\
		typedef options::StringT StringT;									\
		using istream_type = options::istream_type;							\
		using ostream_type = options::ostream_type;							\
		typedef BOOST_ENUM_ARTIFACTS(enum_name)::storage EnumStorage;		\
		typedef BOOST_ENUM_ARTIFACTS(enum_name)::EnumT EnumT;				\
	private:																\
		EnumT value_;														\
																			\
		UnderlyingT get_val_() const override								\
			{ return static_cast<UnderlyingT>(value_); }					\
		void set_val_(UnderlyingT val) override								\
			{ value_ = static_cast<EnumT>(val); }							\
		BOOST_PP_CAT(enum_name, _e)* this_() override{ return this; }		\
																			\
		typedef ::boost::enum_::function_impl::								\
			UnderlyingToEnumImpl<BOOST_PP_CAT(enum_name, _e), options::arbitrary> 	\
			UnderlyingToEnumImpl;											\
	public:																	\

#define BOOST_ENUM_ADAPT_IV(enum_name)										\
		BOOST_PP_CAT(enum_name, _e)(){}										\
		BOOST_PP_CAT(enum_name, _e)(const BOOST_PP_CAT(enum_name, _e)& other) : value_(other.value_){}			\
		BOOST_PP_CAT(enum_name, _e)(const EnumT val) : value_(val){}		\
		operator EnumT() const { return value_; }							\
		BOOST_PP_CAT(enum_name, _e)& operator =(const BOOST_PP_CAT(enum_name, _e)& rhs)							\
						{ value_ = rhs.value_; return *this; }				\
		BOOST_PP_CAT(enum_name, _e)& operator =(EnumT rhs){ value_ = rhs; return *this; }		\
																			\
		explicit BOOST_PP_CAT(enum_name, _e)(UnderlyingT val) :				\
			value_(UnderlyingToEnumImpl::f(val)){}							\
		explicit BOOST_PP_CAT(enum_name, _e)(const StringT& str) :			\
			value_(UnderlyingToEnumImpl::f(EnumStorage::stoe(str))) {}		\
		explicit operator UnderlyingT() const								\
						{ return static_cast<UnderlyingT>(value_); }		\
		explicit operator StringT() const									\
						{ return EnumStorage::etos(static_cast<UnderlyingT>(value_)); }	\
																			\
		static bool has_value(UnderlyingT val)								\
						{ return EnumStorage::has_value(val); }				\
																			\
		friend bool operator ==(const BOOST_PP_CAT(enum_name, _e)&, const BOOST_PP_CAT(enum_name, _e)&);		\
																			\
		};																	\
																			\
	BOOST_ENUM_OVERLOAD_BINARY_OPERATORS(BOOST_PP_CAT(enum_name, _e))		\
																			\
	BOOST_ENUM_OVERLOAD_EQUALITY_OPERATORS(BOOST_PP_CAT(enum_name, _e))		\
																			\
	BOOST_ENUM_OVERLOAD_STREAM_OPERATORS_ADAPT(enum_name, BOOST_PP_CAT(enum_name, _e))\

//! \endcond
#pragma endregion

//! Like BOOST_ENUM_ADAPT, but allows to change the options.
/*!
	Adapts an existing enumeration of the name \a enum_name with custom \a options, enabling it
	to be used similarly to an enumeration defined with the DEFINE macros.
*/
#define BOOST_ENUM_ADAPT_W_OPTIONS(enum_name, options, aseq)				\
	BOOST_ENUM_ADAPT_I(enum_name, options)									\
	BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(aseq)									\
	BOOST_ENUM_ADAPT_II														\
	BOOST_ENUM_NAME_COMMA(aseq)												\
	BOOST_ENUM_ADAPT_III(enum_name)											\
	BOOST_ENUM_INSERT_ENUM_VALUE(aseq)										\
	BOOST_ENUM_ADAPT_IV(enum_name)											\

//! Adapts an existing enumeration. 
/*!
	Adapts an existing enumeration of the name \a enum_name with the standard options, enabling it
	to be used similarly to an enumeration defined with the DEFINE macros.
*/
#define BOOST_ENUM_ADAPT(enum_name, aseq)									\
	BOOST_ENUM_ADAPT_W_OPTIONS(												\
		enum_name,															\
		(::boost::enum_::adapt_options<>),									\
		aseq																\
	)																		\

//namespace example{
//#define FIVE (five)
//#define SIX (six)
//#define SEVEN (seven, "Sieben")
//#define TWENTY (twenty, "Zwanzig")
//
//	enum class AdaptLater{
//		five = 5,
//		six,
//		seven,
//		twenty = 20
//	};
//
//	class _artifacts_AdaptLater{
//		typedef ::boost::enum_::adapt_options<>::options<AdaptLater>::type options;
//		typedef options::UnderlyingT UnderlyingT;
//		typedef AdaptLater EnumT;
//		BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(FIVE)
//		BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(SIX)
//		BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(SEVEN)
//		BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(TWENTY)
//		typedef ::boost::enum_::storage<options>::gen < 
//			BOOST_ENUM_NAME_COMMA(FIVE)
//			BOOST_ENUM_NAME_COMMA(SIX)
//			BOOST_ENUM_NAME_COMMA(SEVEN)
//			BOOST_ENUM_NAME_COMMA(TWENTY)
//		void > ::get storage;
//	}
//
//	
//	class AdaptLater_e : 
//		public ::boost::enum_::function_impl::OrderingImpl<
//			_artifacts_AdaptLater::EnumT, 
//			_artifacts_AdaptLater::options::UnderlyingT, 
//			_artifacts_AdaptLater::options::no_ordering
//		>,
//		public ::boost::enum_::function_impl::BitwiseImpl<
//			AdaptLater_e,
//			_artifacts_AdaptLater::EnumT,
//			_artifacts_AdaptLater::options::UnderlyingT,
//			_artifacts_AdaptLater::options::is_flag
//		>
//	{
//		typedef AdaptLater_e OwnT;
//	public:
//		typedef _artifacts_AdaptLater::options options;
//		typedef ::boost::enum_::supplies::NoCustomSupply supply;
//		typedef options::UnderlyingT UnderlyingT;
//		typedef options::StringT StringT;
//		typedef _artifacts_AdaptLater::storage EnumStorage;
//		typedef _artifacts_AdaptLater::EnumT EnumT;
//	private:
//		EnumT value_;
//
//		UnderlyingT get_val_() const override{ return static_cast<UnderlyingT>(value_); }
//		void set_val_(UnderlyingT val) override{ value_ = static_cast<EnumT>(val); }
//		AdaptLater_e* this_() override{ return this; }
//
//		typedef ::boost::enum_::function_impl::UnderlyingToEnumImpl<AdaptLater_e, options::arbitrary> UnderlyingToEnumImpl;
//	public:
//		BOOST_ENUM_INSERT_ENUM_VALUE(FIVE)
//		BOOST_ENUM_INSERT_ENUM_VALUE(SIX)
//		BOOST_ENUM_INSERT_ENUM_VALUE(SEVEN)
//		BOOST_ENUM_INSERT_ENUM_VALUE(TWENTY)
//
//		AdaptLater_e(){}
//		AdaptLater_e(const AdaptLater_e& other) : value_(other.value_){}
//		AdaptLater_e(const EnumT val) : value_(val){}
//		operator EnumT() const { return value_; }
//		AdaptLater_e& operator =(const AdaptLater_e& rhs){ value_ = rhs.value_; return *this; }
//		AdaptLater_e& operator =(EnumT rhs){ value_ = rhs; return *this; }
//
//		explicit AdaptLater_e(UnderlyingT val) : value_(UnderlyingToEnumImpl::f(val)){}
//		explicit AdaptLater_e(const StringT& str) : value_(UnderlyingToEnumImpl::f(EnumStorage::stoe(str))) {}
//		explicit operator UnderlyingT() const{ return static_cast<UnderlyingT>(value_); }
//		explicit operator StringT() const{ return EnumStorage::etos(static_cast<UnderlyingT>(value_)); }
//
//		static bool has_value(UnderlyingT val){ return EnumStorage::has_value(val); }
//
//		friend bool operator ==(const AdaptLater_e&, const AdaptLater_e&);
//	};
//
//	bool operator ==(const AdaptLater_e& lhs, const AdaptLater_e& rhs){ return lhs.value_ == rhs.value_; }
//	bool operator !=(const AdaptLater_e& lhs, const AdaptLater_e& rhs){ return !(lhs == rhs); }
//
//#ifdef BOOST_NO_CONSTEXPR
//	//overload operators for ValueT <op> ValueT calls
//	template<typename ValueT>
//	typename std::enable_if<std::is_convertible<ValueT, AdaptLater_e>::value && !std::is_same<ValueT, AdaptLater_e>::value, AdaptLater_e>::type
//		operator&(ValueT lhs, ValueT rhs){
//		return AdaptLater_e(lhs) & AdaptLater_e(rhs);
//	}
//	template<typename ValueT>
//	typename std::enable_if<std::is_convertible<ValueT, AdaptLater_e>::value && !std::is_same<ValueT, AdaptLater_e>::value, AdaptLater_e>::type
//		operator|(ValueT lhs, ValueT rhs){
//		return AdaptLater_e(lhs) | AdaptLater_e(rhs);
//	}
//	template<typename ValueT>
//	typename std::enable_if<std::is_convertible<ValueT, AdaptLater_e>::value && !std::is_same<ValueT, AdaptLater_e>::value, AdaptLater_e>::type
//		operator^(ValueT lhs, ValueT rhs){
//		return AdaptLater_e(lhs) ^ AdaptLater_e(rhs);
//	}
//	template<typename ValueT>
//	typename std::enable_if<std::is_convertible<ValueT, AdaptLater_e>::value && !std::is_same<ValueT, AdaptLater_e>::value, AdaptLater_e>::type
//		operator~(ValueT rhs){
//		return ~AdaptLater_e(rhs);
//	}
//#endif
//
//	std::istream& operator>>(std::istream& is, AdaptLater& nt){
//		std::string str;
//		is >> str;
//		try{
//			nt = static_cast<AdaptLater_e>(str);
//		}
//		catch(const std::invalid_argument&){}
//		return is;
//	}
//
//	std::ostream& operator<<(std::ostream& os, const AdaptLater& nt){
//		return os << static_cast<AdaptLater_e::StringT>(static_cast<AdaptLater_e>(nt));
//	}
//
//	enum class AdaptLater2{
//		five = 5,
//		six,
//		seven,
//		twenty = 20
//	};
//
//	BOOST_ENUM_ADAPT_I(AdaptLater2, (::boost::enum_::adapt_options<>))
//	BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(FIVE SIX SEVEN TWENTY)
//	BOOST_ENUM_ADAPT_II
//	BOOST_ENUM_NAME_COMMA(FIVE SIX SEVEN TWENTY)
//	BOOST_ENUM_ADAPT_III(AdaptLater2)
//	BOOST_ENUM_INSERT_ENUM_VALUE(FIVE SIX SEVEN TWENTY)
//	BOOST_ENUM_ADAPT_IV(AdaptLater2)
//}

#endif