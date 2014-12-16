// TestingStuff.cpp : Defines the entry point for the console application.
//

#include <type_traits>

template<class Type, class ValueT, bool active>
class ImplAdd{
};

template<class Type, class ValueT>
class ImplAdd < Type, ValueT, true > {
	int get_val_inte() const{
		return this_()->get_val_impl();
	}
	void set_val_inte(int i){
		this_()->set_val_impl(i);
	}
	Type* this_(){ return static_cast<Type*>(this); }
	const Type* this_() const{ return static_cast<const Type*>(this); }
public:
	typedef Type Type;
	Type& operator +=(const Type& x){
		set_val_inte(get_val_inte() + x.get_val_inte());
		return *this_();
	}

	friend Type operator+(const Type& lhs, const Type& rhs){
		Type ret = lhs;
		return ret += rhs;
	}
};

namespace things{
	namespace artifacts{
		enum class ValueT{
			zero, one, two
		};
	}

	class MyEnum : public ImplAdd < MyEnum, artifacts::ValueT, true > {
		typedef artifacts::ValueT ValueT;
		friend class ImplAdd < MyEnum, ValueT, true > ;
		int get_val_impl() const{
			return (int)value;
		}
		void set_val_impl(int v){
			value = (ValueT)v;
		}
		typedef  int UnderlyingT;
		ValueT value;
	public:
		static const ValueT zero = artifacts::ValueT::zero;
		static const ValueT one = artifacts::ValueT::one;
		static const ValueT two = artifacts::ValueT::two;

		MyEnum(ValueT x) : value(x){}
		MyEnum(const MyEnum& other) : value(other.value){}
	};

	template<typename ValueT>
	typename std::enable_if<std::is_convertible<ValueT, MyEnum>::value && !std::is_same<ValueT, MyEnum>::value, MyEnum>::type 
	operator+(ValueT lhs, ValueT rhs){
		return MyEnum(lhs) + MyEnum(rhs);
	}
}
//MyEnum operator+(artifacts::ValueT lhs, artifacts::ValueT rhs){
//	return MyEnum(lhs) + MyEnum(rhs);
//}
//
//enum class FooValueT{
//	zero, one, two
//};
//
//class Foo{
//	FooValueT val_;
//public:
//	Foo(FooValueT x) : val_(x){};
//
//	Foo& operator+=(Foo other){
//		val_ = (FooValueT)((int)val_ + (int)other.val_);
//		return *this;
//	}
//
//	friend Foo operator+(Foo lhs, Foo rhs){
//		Foo ret = lhs;
//		return ret += lhs;
//	}
//
//	friend Foo operator+(FooValueT lhs, FooValueT rhs);/*{
//		return (Foo)lhs + (Foo)rhs;
//	}*/
//};
//
//Foo operator+(FooValueT lhs, FooValueT rhs){
//	return (Foo)lhs + (Foo)rhs;
//}

using things::MyEnum;

int main(int argc, char* argv[])
{
	MyEnum myM = MyEnum::zero;
	myM += MyEnum::one;
	myM = MyEnum::zero + MyEnum::two;
	//Foo myF = FooValueT::zero;
	//myF += FooValueT::one;
	//myF = Foo(FooValueT::zero) + FooValueT::two;
	//myF = FooValueT::zero + Foo(FooValueT::two);
	//myF = FooValueT::zero + FooValueT::two;
	return 0;
}
