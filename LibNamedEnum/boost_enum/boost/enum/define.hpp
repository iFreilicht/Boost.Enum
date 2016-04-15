
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


/*! \file define.hpp
	\brief Contains all macros necessary to define new enumerations.
*/


#ifndef BOOST_ENUM_IG_DEFINE_HPP
#define BOOST_ENUM_IG_DEFINE_HPP

#include <boost/enum/config/config.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/enum/macros/define_name_value_pair.hpp>
#include <boost/enum/macros/define_enum_value.hpp>
#include <boost/enum/macros/name_comma.hpp>
#include <boost/enum/macros/insert_enum_value.hpp>
#include <boost/enum/macros/artifacts_namespace.hpp>
#include <boost/enum/macros/overload_binary_operators.hpp>
#include <boost/enum/macros/overload_stream_operators.hpp>
#include <boost/enum/macros/overload_equality_operators.hpp>

#include <boost/enum/storage/storage.hpp>
#include <boost/enum/options.hpp>
#include <boost/enum/storage/function_impl.hpp>

#pragma region Implementation
//! \cond DefineImpl
/////////////////////////////////////////////////////////////////////////////
// All macros in this region are used for implementing and should not be used!
// They are subject to change, just like private member functions.
/////////////////////////////////////////////////////////////////////////////

#define BOOST_ENUM_DEFINE_I(enum_name, options_)							\
	BOOST_ENUM_ENTER_ARTIFACTS_NS(enum_name)								\
		typedef BOOST_PP_CAT(BOOST_PP_REM, options_) options;				\
		typedef options::StringT StringT;									\
		typedef options::Supply supply;										\
		typedef options::UnderlyingT UnderlyingT;							\
		enum class index : std::make_unsigned<UnderlyingT>::type{			\

#define BOOST_ENUM_DEFINE_II(enum_name)										\
		};																	\
		enum class EnumT : UnderlyingT{										\


#define BOOST_ENUM_DEFINE_III(enum_name)									\
		};																	\

#define BOOST_ENUM_DEFINE_IV(enum_name)										\
		typedef ::boost::enum_::											\
			storage<options>::gen <											\

#define BOOST_ENUM_DEFINE_V(enum_name)										\
		void > ::get storage;												\
	BOOST_ENUM_EXIT_ARTIFACTS_NS											\
	class enum_name :														\
		public ::boost::enum_::function_impl::OrderingImpl<					\
			BOOST_ENUM_ARTIFACTS(enum_name)::EnumT,							\
			BOOST_ENUM_ARTIFACTS(enum_name)::options::UnderlyingT,			\
			BOOST_ENUM_ARTIFACTS(enum_name)::options::no_ordering			\
				>,															\
		public ::boost::enum_::function_impl::BitwiseImpl<					\
			enum_name,														\
			BOOST_ENUM_ARTIFACTS(enum_name)::EnumT,							\
			BOOST_ENUM_ARTIFACTS(enum_name)::options::UnderlyingT,			\
			BOOST_ENUM_ARTIFACTS(enum_name)::options::is_flag				\
		>																	\
	{																		\
		typedef enum_name OwnT;												\
	public:																	\
		typedef BOOST_ENUM_ARTIFACTS(enum_name)::options options;			\
		typedef options::Supply supply;										\
		typedef options::UnderlyingT UnderlyingT;							\
		typedef options::StringT StringT;									\
		using istream_type = options::istream_type;							\
		using ostream_type = options::ostream_type;							\
		typedef BOOST_ENUM_ARTIFACTS(enum_name)::storage EnumStorage;		\
		typedef BOOST_ENUM_ARTIFACTS(enum_name)::EnumT EnumT;				\
	private:																\
		EnumT value_;														\
		UnderlyingT get_val_() const override								\
			{ return static_cast<UnderlyingT>(value_); }					\
		void set_val_(UnderlyingT val) override								\
			{ value_ = static_cast<EnumT>(val); }							\
		enum_name* this_() override { return this; }						\
		typedef ::boost::enum_::function_impl::UnderlyingToEnumImpl			\
			<enum_name, options::arbitrary> UnderlyingToEnumImpl;			\
	public:																	\

//if expl_conv is 1, conversions to UnderlyingT are explicit, 
//if it is 0, they're implicit. Not to be exposed!
#define BOOST_ENUM_DEFINE_VI(enum_name, expl_conv)							\
		enum_name(){}														\
		enum_name(const enum_name& other) : value_(other.value_){}			\
		enum_name(const EnumT val) : value_(val){}							\
		operator EnumT() const { return value_; }							\
		enum_name& operator =(const enum_name& rhs)							\
			{ value_ = rhs.value_; return *this; }							\
		enum_name& operator =(EnumT rhs)									\
			{ value_ = rhs; return *this; }									\
																			\
		BOOST_PP_EXPR_IIF(expl_conv, explicit) enum_name(UnderlyingT val) :	\
			value_(UnderlyingToEnumImpl::f(val)){}							\
		explicit enum_name(const StringT& str) :							\
			value_(UnderlyingToEnumImpl::f(EnumStorage::stoe(str))) {}		\
		BOOST_PP_EXPR_IIF(expl_conv, explicit) operator UnderlyingT() const	\
			{ return static_cast<UnderlyingT>(value_); }					\
		explicit operator StringT() const									\
			{ return EnumStorage::etos(static_cast<UnderlyingT>(value_)); }	\
																			\
		static bool has_value(UnderlyingT val)								\
			{ return EnumStorage::has_value(val); }							\
		static const std::vector<UnderlyingT>& values()						\
			{ return EnumStorage::valuevec(); }								\
																			\
		friend bool operator ==(const enum_name&, const enum_name&);		\
																			\
	};																		\

#define BOOST_ENUM_DEFINE_VII(enum_name)									\
																			\
	BOOST_ENUM_OVERLOAD_BINARY_OPERATORS(enum_name)							\
																			\
	BOOST_ENUM_OVERLOAD_EQUALITY_OPERATORS(enum_name)						\
																			\
	BOOST_ENUM_OVERLOAD_STREAM_OPERATORS(enum_name)							\
																			\

/*
	Intellisenses preprocessor contains a bug that would incorrectly mark any
	occurences of this macro as ill-formed code, a workaround is needed.
	Using this workaround hides the correct values from intellisense, though.
	Every value will be displayed as 0.
*/
#if defined BOOST_ENUM_DISABLE_INTELLISENSE_WORKAROUND || !defined __INTELLISENSE__

#define BOOST_ENUM_DEFINE_IMPL(enum_name, options, dseq, expl_conv)			\
	BOOST_ENUM_DEFINE_I(enum_name, options)									\
	BOOST_ENUM_NAME_COMMA(dseq)												\
	BOOST_ENUM_DEFINE_II(enum_name)											\
	BOOST_ENUM_DEFINE_ENUM_VALUE(dseq)										\
	BOOST_ENUM_DEFINE_III(enum_name)										\
	BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(dseq)									\
	BOOST_ENUM_DEFINE_IV(enum_name)											\
	BOOST_ENUM_NAME_COMMA(dseq)												\
	BOOST_ENUM_DEFINE_V(enum_name)											\
	BOOST_ENUM_INSERT_ENUM_VALUE(dseq)										\
	BOOST_ENUM_DEFINE_VI(enum_name, expl_conv)								\

#else
//WARNING! IntelliSense will not display the correct values!
#define BOOST_ENUM_DEFINE_IMPL(enum_name, options, dseq, expl_conv)			\
	BOOST_ENUM_DEFINE_I(enum_name, options)									\
	/*BOOST_ENUM_NAME_COMMA(dseq)*/											\
	BOOST_ENUM_DEFINE_II(enum_name)											\
	/*BOOST_ENUM_DEFINE_ENUM_VALUE(dseq)*/									\
	BOOST_ENUM_DEFINE_III(enum_name)										\
	/*BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(dseq)*/								\
	BOOST_ENUM_DEFINE_IV(enum_name)											\
	/*BOOST_ENUM_NAME_COMMA(dseq)*/											\
	BOOST_ENUM_DEFINE_V(enum_name)											\
	BOOST_ENUM_INSERT_ENUM_VALUE(dseq)										\
	BOOST_ENUM_DEFINE_VI(enum_name, expl_conv)								\


#endif
//! \endcond
#pragma endregion


//!Like BOOST_ENUM_DEFINE_W_OPTIONS if the new enumeration should be part of a class.
/*!
	Defines a new enumeration of the name \a enum_name with custom \a options
	based on \a seq.
	Requires BOOST_ENUM_DEFINE_IN_CLASS_II to be used after the class definition.
*/
#define BOOST_ENUM_DEFINE_IN_CLASS_I_W_OPTIONS(enum_name, options, dseq)	\
	BOOST_ENUM_DEFINE_IMPL(enum_name, options, dseq, 1)						\

//! Like BOOST_ENUM_DEFINE if the new enumeration should be part of a class.
/*! 
	Defines a new enumeration of the name \a enum_name with the standard options
	based on \a seq.
	Requires #BOOST_ENUM_DEFINE_IN_CLASS_II(enum_name) to be 
	used after the class definition.
*/
#define BOOST_ENUM_DEFINE_IN_CLASS_I(enum_name, dseq)						\
	BOOST_ENUM_DEFINE_IN_CLASS_I_W_OPTIONS(enum_name,						\
		(::boost::enum_::options<>), dseq)									\

//! Use after class with _IN_CLASS_I macro inside it
/*!
	To be used after a class that had #BOOST_ENUM_DEFINE_IN_CLASS_I or
	#BOOST_ENUM_DEFINE_IN_CLASS_I_W_OPTIONS used inside it.
	Has to be used once for each enumeration defined in that class.
*/
#define BOOST_ENUM_DEFINE_IN_CLASS_II(enum_name)							\
	BOOST_ENUM_DEFINE_VII(enum_name)										\

//TODO: Forward declaration
//#define BOOST_ENUM_FWD_DECLARE(enum_name, underlyingT)					\
//	BOOST_ENUM_ENTER_ARTIFACTS_NS(enum_name)								\
//	enum class EnumT : underlyingT;											\
//	BOOST_ENUM_EXIT_ARTIFACTS_NS											\
//	typedef BOOST_ENUM_ARTIFACTS(enum_name)::EnumT enum_name;				\


//! Like BOOST_ENUM_DEFINE, but allows to change the options.
/*!
	Defines a new enumeration of the name \a enum_name with custom \a options
	based on \a seq.
*/
#define BOOST_ENUM_DEFINE_W_OPTIONS(enum_name, options, dseq)				\
	BOOST_ENUM_DEFINE_IN_CLASS_I_W_OPTIONS(enum_name, options, dseq)		\
	BOOST_ENUM_DEFINE_IN_CLASS_II(enum_name)								\


//! Defines new enumeration.
/*!
    Defines a new enumeration of the name \a enum_name with the standard options
	based on \a seq.
*/
#define BOOST_ENUM_DEFINE(enum_name, dseq)									\
	BOOST_ENUM_DEFINE_IN_CLASS_I(enum_name, dseq)							\
	BOOST_ENUM_DEFINE_IN_CLASS_II(enum_name)								\



/*


namespace example{
#define FIVE (five, (5))
#define SIX (six)
#define SEVEN (seven, _, "Sieben")
#define TWENTY (twenty, (20), "Zwanzig")


	class _artifacts_NewTest{ public:
			typedef ::boost::enum_::options<0> options;
			typedef options::StringT StringT;
			typedef options::Supply supply;
			typedef options::UnderlyingT UnderlyingT;
			enum class index : std::make_unsigned<UnderlyingT>::type{
				BOOST_ENUM_NAME_COMMA(FIVE)
				BOOST_ENUM_NAME_COMMA(SIX)
				BOOST_ENUM_NAME_COMMA(SEVEN)
				BOOST_ENUM_NAME_COMMA(TWENTY)
			};
			enum class EnumT : UnderlyingT {
				BOOST_ENUM_DEFINE_ENUM_VALUE(FIVE)
				BOOST_ENUM_DEFINE_ENUM_VALUE(SIX)
				BOOST_ENUM_DEFINE_ENUM_VALUE(SEVEN)
				BOOST_ENUM_DEFINE_ENUM_VALUE(TWENTY)
			};
			BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(FIVE)
			BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(SIX)
			BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(SEVEN)
			BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(TWENTY)
			typedef ::boost::enum_::storage<options>::gen < 
				BOOST_ENUM_NAME_COMMA(FIVE)
				BOOST_ENUM_NAME_COMMA(SIX)
				BOOST_ENUM_NAME_COMMA(SEVEN)
				BOOST_ENUM_NAME_COMMA(TWENTY)
			void > ::get storage;
		
	};

	
	class NewTest : 
		public ::boost::enum_::function_impl::OrderingImpl<
			_artifacts_NewTest::EnumT, 
			_artifacts_NewTest::options::UnderlyingT, 
			_artifacts_NewTest::options::no_ordering
		>,
		public ::boost::enum_::function_impl::BitwiseImpl<
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
		using istream_type = options::istream_type;
		using ostream_type = options::ostream_type;
		typedef _artifacts_NewTest::storage EnumStorage;
		typedef _artifacts_NewTest::EnumT EnumT;
	private:
		EnumT value_;

		UnderlyingT get_val_() const override{ return static_cast<UnderlyingT>(value_); }
		void set_val_(UnderlyingT val) override{ value_ = static_cast<EnumT>(val); }
		NewTest* this_() override{ return this; }

		typedef ::boost::enum_::function_impl::UnderlyingToEnumImpl<NewTest, options::arbitrary> UnderlyingToEnumImpl;
	public:
		BOOST_ENUM_INSERT_ENUM_VALUE(FIVE)
		BOOST_ENUM_INSERT_ENUM_VALUE(SIX)
		BOOST_ENUM_INSERT_ENUM_VALUE(SEVEN)
		BOOST_ENUM_INSERT_ENUM_VALUE(TWENTY)

		NewTest(){}
		NewTest(const NewTest& other) : value_(other.value_){}
		NewTest(const EnumT val) : value_(val){}
		operator EnumT() const { return value_; }
		NewTest& operator =(const NewTest& rhs){ value_ = rhs.value_; return *this; }
		NewTest& operator =(EnumT rhs){ value_ = rhs; return *this; }

		BOOST_PP_EXPR_IIF(1, explicit) NewTest(UnderlyingT val) : value_(UnderlyingToEnumImpl::f(val)){}
		explicit NewTest(const StringT& str) : value_(UnderlyingToEnumImpl::f(EnumStorage::stoe(str))) {}

		BOOST_PP_EXPR_IIF(1, explicit) operator UnderlyingT() const{ return static_cast<UnderlyingT>(value_); }
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

	BOOST_ENUM_OVERLOAD_STREAM_OPERATORS(NewTest)

	//making the enum unscoped 
	//works in classes and namespaces
	//doesn't seem to be possible with macros
	struct Wrap{
	static const NewTest::EnumT five = static_cast<NewTest::EnumT>(NewTest::five);
	static const NewTest::EnumT six = static_cast<NewTest::EnumT>(NewTest::six);
	static const NewTest::EnumT seven = static_cast<NewTest::EnumT>(NewTest::seven);
	static const NewTest::EnumT twenty = static_cast<NewTest::EnumT>(NewTest::twenty);
	};

	Wrap thing;
	Wrap* p_thing = &thing;
	NewTest test = thing.seven;
	NewTest test2 = p_thing->six;

	BOOST_ENUM_DEFINE_I(NewTest2, (::boost::enum_::options<>))
	BOOST_ENUM_NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ENUM_DEFINE_II(NewTest2)
	BOOST_ENUM_DEFINE_ENUM_VALUE(FIVE SIX SEVEN TWENTY)
	BOOST_ENUM_DEFINE_III(NewTest2)
	BOOST_ENUM_DEFINE_NAME_VALUE_PAIR(FIVE SIX SEVEN TWENTY)
	BOOST_ENUM_DEFINE_IV(NewTest2)
	BOOST_ENUM_NAME_COMMA(FIVE SIX SEVEN TWENTY)
	BOOST_ENUM_DEFINE_V(NewTest2)
	BOOST_ENUM_INSERT_ENUM_VALUE(FIVE SIX SEVEN TWENTY)
	BOOST_ENUM_DEFINE_VI(NewTest2, 1)
	BOOST_ENUM_DEFINE_VII(NewTest2)



	
}

/**/

#endif