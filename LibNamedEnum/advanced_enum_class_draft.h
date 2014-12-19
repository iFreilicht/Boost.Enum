#include "options.h"
#include "enum_storage.hpp"


class IAdvanced_enum{
	enum class EnumType{};
public:
	typedef ::boost::advanced_enum::Options<> options;
	typedef options::UnderlyingT UnderlyingT;
	typedef options::StringT StringT;
	typedef ::boost::advanced_enum::enum_storage<options> EnumStorage;
	typedef EnumType EnumT;

	IAdvanced_enum();
	IAdvanced_enum(const IAdvanced_enum& other);
	IAdvanced_enum(const EnumT val);
	operator EnumT() const;
	IAdvanced_enum& operator =(const IAdvanced_enum& rhs);
	IAdvanced_enum& operator =(EnumT rhs);

	explicit IAdvanced_enum(UnderlyingT val);
	explicit IAdvanced_enum(const StringT& str);
	explicit operator UnderlyingT() const;
	explicit operator StringT() const;

	static bool has_value(UnderlyingT val);

	friend bool operator ==(const IAdvanced_enum&, const IAdvanced_enum&);
};

bool operator ==(const IAdvanced_enum& lhs, const IAdvanced_enum& rhs);
bool operator !=(const IAdvanced_enum& lhs, const IAdvanced_enum& rhs);

//overload operators for ValueT <op> ValueT calls
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IAdvanced_enum>::value && !std::is_same<ValueT, IAdvanced_enum>::value, IAdvanced_enum>::type
operator&(ValueT lhs, ValueT rhs){
	return IAdvanced_enum(lhs) & IAdvanced_enum(rhs);
}
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IAdvanced_enum>::value && !std::is_same<ValueT, IAdvanced_enum>::value, IAdvanced_enum>::type
operator|(ValueT lhs, ValueT rhs){
	return IAdvanced_enum(lhs) | IAdvanced_enum(rhs);
}
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IAdvanced_enum>::value && !std::is_same<ValueT, IAdvanced_enum>::value, IAdvanced_enum>::type
operator^(ValueT lhs, ValueT rhs){
	return IAdvanced_enum(lhs) ^ IAdvanced_enum(rhs);
}
template<typename ValueT>
typename std::enable_if<std::is_convertible<ValueT, IAdvanced_enum>::value && !std::is_same<ValueT, IAdvanced_enum>::value, IAdvanced_enum>::type
operator~(ValueT rhs){
	return ~IAdvanced_enum(rhs);
}

std::istream& operator>>(std::istream& is, IAdvanced_enum& nt){
	std::string str;
	is >> str;
	try{
		nt = static_cast<IAdvanced_enum>(str);
	}
	catch (const std::invalid_argument&){}
	return is;
}

std::ostream& operator<<(std::ostream& os, const IAdvanced_enum& nt){
	return os << static_cast<IAdvanced_enum::StringT>(nt);
}
