
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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


#define BOOST_ENUM_ADAPT_W_OPTIONS(enum_name, options, seq)					\
	BOOST_ENUM_ADAPT_I(enum_name, options)									\
	BOOST_ENUM_ADAPT_NAME_VALUE_PAIR(seq)									\
	BOOST_ENUM_ADAPT_II														\
	BOOST_ENUM_NAME_COMMA(seq)												\
	BOOST_ENUM_ADAPT_III(enum_name)											\
	BOOST_ENUM_INSERT_ENUM_VALUE(seq)										\
	BOOST_ENUM_ADAPT_IV(enum_name)											\

#define BOOST_ENUM_ADAPT(enum_name, seq)									\
	BOOST_ENUM_ADAPT_W_OPTIONS(												\
		enum_name,															\
		(::boost::enum_::adapt_options<>),									\
		seq																	\
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