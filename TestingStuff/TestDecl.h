
#pragma once

template<class Type, bool active>
struct ImplAdd{
	virtual int get_val_() const = 0;
	virtual void set_val_(int) = 0;
};

template<class Type>
class ImplAdd < Type, true > {
	virtual int get_val_() const = 0;
	virtual void set_val_(int) = 0;
	Type* this_(){ return (Type*)this; }
public:
	void set(int val){
		set_val(val);
	}

	Type& operator +=(const Type& x){
		val_() += ((ImplSet&)x).val_();
		return *this_();
	}

	friend Type& operator+(const Type& lhs, const Type& rhs){
		Type ret = lhs;
		return ret += rhs;
	}
};

