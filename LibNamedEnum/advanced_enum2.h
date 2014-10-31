
#pragma once

#include "enum_storage2.hpp"
#ifdef __EDG__
#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1
#endif
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple.hpp>
#include <string>

namespace boost{
	namespace advanced_enum{
		template<typename EnumT, typename UnderlyingT>
		class advanced_base{
			EnumT value_;
		public:
			typedef EnumT EnumT;
			typedef UnderlyingT UnderlyingT;

			advanced_base(EnumT value) : 
				value_
			{}
			operator EnumT(){
				return value_;
			}

			operator std::string(){
				return Storage::etos(value_);
			}
		};

		template<typename EnumT>
		struct advanced;


	}
}

#pragma region DEFINE_NAME_VALUE_PAIR

//takes tuple like (name), (name, value) or (name, value, string)
#define BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR(tuple) BOOST_PP_CAT(BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR_, BOOST_PP_TUPLE_SIZE(tuple))(tuple)

#define BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR_1(tuple)                          \
    struct BOOST_PP_TUPLE_ELEM(0, tuple){ \
        static const std::string name; \
        static const EnumT value = EnumT::BOOST_PP_TUPLE_ELEM(0, tuple); \
    };  \
    const std::string BOOST_PP_TUPLE_ELEM(0, tuple)::name = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, tuple))

#define BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR_2(tuple) \
	BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR_1(tuple)

#define BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR_3(tuple) \
    struct BOOST_PP_TUPLE_ELEM(0, tuple){ \
        static const std::string name; \
        static const EnumT value = EnumT::BOOST_PP_TUPLE_ELEM(0, tuple); \
    };  \
    const std::string BOOST_PP_TUPLE_ELEM(0, tuple)::name = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, tuple))

#pragma endregion


#define BOOST_ADVENUM__GET_SUPPLY_VALUE(enum_name,supply,name) \
	::boost::advanced_enum::supplies::at<supply::values, \
		static_cast<unsigned int>(::boost::advanced_enum::artifacts::BOOST_PP_CAT(enum_name,_)::index::name)>::value



#define BOOST_ADVENUM_DEFINE(enum_name, ...)


#define STRUCT(tuple) int BOOST_PP_TUPLE_ELEM(0, tuple) = 0;

namespace boost{
	namespace advanced_enum{
		namespace artifacts{
			namespace Zot_{
				typedef int UnderlyingT;
				enum class index : unsigned int{
					zero,
					one,
					two
				};
			}
		}
	}
}

enum class Zot{
	zero = BOOST_ADVENUM__GET_SUPPLY_VALUE(Zot,boost::advanced_enum::supplies::increment<int>,zero),
	one = BOOST_ADVENUM__GET_SUPPLY_VALUE(Zot, boost::advanced_enum::supplies::increment<int>, zero),
	two = BOOST_ADVENUM__GET_SUPPLY_VALUE(Zot, boost::advanced_enum::supplies::increment<int>, zero),
};


namespace boost{
	namespace advanced_enum{
		namespace artifacts{
			namespace Zot_{
				typedef Zot EnumT;
				BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR((zero));
				BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR((one));
				BOOST_ADVENUM__DEFINE_NAME_VALUE_PAIR((two));
				typedef boost::advanced_enum::enum_storage<Zot>::gen<zero, one, two>::get Storage;
			}
		}

		template<>
		struct advanced < Zot > : advanced_base < Zot, int >
		{
			typedef artifacts::Zot_::Storage Storage;
			typedef advanced_base < Zot, int > Base;
			typedef Base::EnumT EnumT;
		private:

		public:
			advanced(EnumT v) : Base(v){};

		};
	}
}

using namespace boost::advanced_enum;

std::string one = advanced<Zot>(Zot::one);


BOOST_ADVENUM_DEFINE(Zott,
	(zero),
	(one),
	(two),
	(three)
);