
//          Copyright Felix Uhl 2014-2016
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


//===========================================
//===========================================
//============== UNUSED!!! ==================
//===========================================
//===========================================

#ifndef BOOST_ENUM_IG_CLASS_DRAFT_HPP
#define BOOST_ENUM_IG_CLASS_DRAFT_HPP

#include <boost/enum/options/options.hpp>
#include <boost/enum/storage/storage.hpp>


class IEnum{
	enum class EnumType{};
public:
	typedef ::boost::enum_::options<> options;
	typedef options::UnderlyingT UnderlyingT;
	typedef options::StringT StringT;
	typedef ::boost::enum_::storage<options> EnumStorage;
	typedef EnumType EnumT;

	IEnum();
	IEnum(const IEnum& other);
	IEnum(const EnumT val);
	operator EnumT() const;
	IEnum& operator =(const IEnum& rhs);
	IEnum& operator =(EnumT rhs);

	explicit IEnum(UnderlyingT val);
	explicit IEnum(const StringT& str);
	explicit operator UnderlyingT() const;
	explicit operator StringT() const;

	static bool has_value(UnderlyingT val);

	friend bool operator ==(const IEnum&, const IEnum&);
};

bool operator ==(const IEnum& lhs, const IEnum& rhs);
bool operator !=(const IEnum& lhs, const IEnum& rhs);

//overload operators for ValueT <op> ValueT calls
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IEnum>::value && !std::is_same<ValueT, IEnum>::value, IEnum>::type
operator&(ValueT lhs, ValueT rhs){
	return IEnum(lhs) & IEnum(rhs);
}
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IEnum>::value && !std::is_same<ValueT, IEnum>::value, IEnum>::type
operator|(ValueT lhs, ValueT rhs){
	return IEnum(lhs) | IEnum(rhs);
}
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IEnum>::value && !std::is_same<ValueT, IEnum>::value, IEnum>::type
operator^(ValueT lhs, ValueT rhs){
	return IEnum(lhs) ^ IEnum(rhs);
}
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IEnum>::value && !std::is_same<ValueT, IEnum>::value, IEnum>::type
operator~(ValueT rhs){
	return ~IEnum(rhs);
}

std::istream& operator>>(std::istream& is, IEnum& nt){
	std::string str;
	is >> str;
	try{
		nt = static_cast<IEnum>(str);
	}
	catch (const std::invalid_argument&){}
	return is;
}

std::ostream& operator<<(std::ostream& os, const IEnum& nt){
	return os << static_cast<IEnum::StringT>(nt);
}


#endif