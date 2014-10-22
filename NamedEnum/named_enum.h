
#ifndef BOOST_NAMEDENUM_HPP
#define BOOST_NAMEDENUM_HPP

#include "stdafx.h"
#ifdef __EDG__
#define BOOST_PP_VARIADICS 1
#define BOOST_PP_VARIADICS_MSVC 1
#endif
#include <boost\preprocessor\seq\for_each.hpp>
#include <boost\preprocessor\seq\transform.hpp>
#include <boost\preprocessor\variadic\to_seq.hpp>
#include <string>
#include <map>
namespace boost{
	namespace named_enum{		
		//enum value supplies are simple template structs that take an integer as their template argument and have the identifiers value and start
		//to represent a convention after which the underlying values of named_enums are generated
		namespace supplies{
			//supply that shifts Val left py one
			template<int Val>
			struct shiftL1{
				enum{ value = Val << 1, start = 1 };
			};

			//supply that increments val
			template<int Val>
			struct increment{
				enum{ value = Val + 1, start = 0 };
			};

			//supply creator for arbitrary values
			template<int CurrVal, int ... RemVals>
			struct arbitrary{
				//supply that can store arbitrary values
				template<int val>
				struct values{
					enum{ value = arbitrary<RemVals ...>::values<val>::value, start = CurrVal };
				};

				template<>
				struct values < CurrVal > {
					enum{ value = arbitrary<RemVals ...>::values<CurrVal>::start, start = CurrVal };
				};
			};
			//specialisation so that all values past the last one are the same
			template<int CurrVal>
			struct arbitrary < CurrVal > {
				template<int val>
				struct values{
					enum{ value = CurrVal, start = CurrVal };
				};
			};
		}


		//this class can be typedef-d to offer conversions from and to std::string
		template<typename EnumT, template<int> class Supply = supplies::increment, typename LastEntry = void>
		class named_enum{
		private:
			////-------linked list------------
			//entry that represents one enum value
			template<const char* Name, typename PrevEntry>
			struct value_entry{
				typedef PrevEntry prev;
				const std::string name = Name;
				enum{ int_value = Supply<PrevEntry::int_value>::value };

				void insert_into_stoemap(std::map<std::string, EnumT>& map){
					prev().insert_into_stoemap(map);
					map.insert(std::pair<std::string, EnumT>(name, static_cast<EnumT>(int_value)));
				}

				void insert_into_etosmap(std::map<EnumT, std::string>& map){
					prev().insert_into_etosmap(map);
					map.insert(std::pair<EnumT, std::string>(static_cast<EnumT>(int_value), name));
				}
			};

			//specialisation for the first element
			template <const char* Name>
			struct value_entry < Name, void > {
				typedef void prev;
				const std::string name = Name;
				enum{ int_value = Supply<0>::start };

				void insert_into_stoemap(std::map<std::string, EnumT>& map){
					map.insert(std::pair<std::string, EnumT>(name, static_cast<EnumT>(int_value)));
				}

				void insert_into_etosmap(std::map<EnumT, std::string>& map){
					map.insert(std::pair<EnumT, std::string>(static_cast<EnumT>(int_value), name));
				}
			};

			////-----lookup maps--------
			//map for fast lookup of strings
			std::map<std::string, EnumT> stoemap_;
			//map for fast lookup of enum values
			std::map<EnumT, std::string> etosmap_;
				
			//singleton instance
			static named_enum& instance(){
				static named_enum instance_;
				return instance_;
			}

			//init method for stoemap
			void init_stoemap(){
				stoemap_.clear();
				LastEntry().insert_into_stoemap(stoemap_);
			}
			//do a lookup
			EnumT stoe_map_lookup(const std::string& key){
				return stoemap_.at(key);
			}

			//init method for etosmap
			void init_etosmap(){
				etosmap_.clear();
				LastEntry().insert_into_etosmap(etosmap_);
			}
			//do a lookup
			std::string etos_map_lookup(EnumT key){
				return etosmap_.at(key);
			}

			////------generator------
			//type with same arguments except LastEntry
			template<typename LastEntry2>
			struct with_last{
				typedef named_enum<EnumT, Supply, LastEntry2> get;
			};
			//generate named_enum
			template<typename PrevEntry, const char* entry_name, const char* ... next_entries>
			struct generator{
				typedef typename named_enum::template value_entry<entry_name, PrevEntry> entry;
				typedef typename generator<entry, next_entries ...>::enumeration enumeration;
			};
			//final case
			template<typename PrevEntry, const char* entry_name>
			struct generator < PrevEntry, entry_name > {
				typedef typename named_enum::template value_entry<entry_name, PrevEntry> entry;
				typedef typename named_enum::template with_last<entry>::get enumeration;
			};

			/////-------indexing-------
			//number of elements
			template<typename curr_entry>
			struct number_of_elements{
				enum{ value = 1 + number_of_elements<curr_entry::prev>::value };
			};
			//final case for first element
			template<>
			struct number_of_elements < void > {
				enum{ value = 0 };
			};

			//like using curr_entry(::prev){index}::value
			template<typename curr_entry, int index>
			struct int_at_index{
				typedef typename curr_entry::prev prev;
				enum { value = int_at_index<prev, index - 1>::value };
			};
			//final case
			template<typename curr_entry>
			struct int_at_index < curr_entry, 0 > {
				enum { value = curr_entry::int_value };
			};


			////-----------conversion------------
			//convert string to EnumT at runtime
			template<typename curr_entry>
			static EnumT stoe_linear_lookup(const std::string& name){
				if (name == curr_entry().name)
					return static_cast<EnumT>(curr_entry::int_value);
				else
					return stoe_linear_lookup<typename curr_entry::prev>(name);
			}
			//failure case when curr_entry is void
			template<>
			static inline EnumT stoe_linear_lookup<void>(const std::string& name){
				throw std::bad_cast();
				return static_cast<EnumT>(0);
			}

			//convert EnumT to string at compiletime (only works with literals and constants)
			template<typename curr_entry, int value, int CurrVal = curr_entry::int_value>
			struct etos_compiletime{
				static inline std::string get(){
					return etos_compiletime<curr_entry::prev, value>::get();
				}
			};
			//success case when value and CurrVal are equal
			template<typename curr_entry, int value>
			struct etos_compiletime < curr_entry, value, value > {
				static inline std::string get(){
					return curr_entry().name;
				}
			};

			//convert EnumT to string at runtime
			template<typename curr_entry>
			static std::string etos_linear_lookup(int value){
				if (value == curr_entry::int_value)
					return curr_entry().name;
				else
					return etos_linear_lookup<curr_entry::prev>(value);
			}
			//failure case when curr_entry is void (which shouldn't ever happen)
			template<>
			static inline std::string etos_linear_lookup<void>(int value){
				throw std::bad_cast();
				return "";
			}
		public:
			//generator to create a named_enum like so: named_enum<EnumT[, Supply]>::gen<entry{, entry}>::get
			template<const char* ... entries>
			struct gen{
				typedef typename generator<void, entries ...>::enumeration get;
			};

			//number of elements
			enum{ num_vals = number_of_elements<LastEntry>::value };

			//initialise lookup maps (not required, but recommended for large enums)
			static void init_lookupmaps(){
				instance().init_etosmap();
				instance().init_stoemap();
			}

			//convert string to EnumT at runtime
			static EnumT stoe(const std::string& name){
				if (instance().stoemap_.empty()){
					return stoe_linear_lookup<LastEntry>(name);
				}
				else{
					return instance().stoe_map_lookup(name);
				}
			}

			//convert EnumT to string at compiletime
			template<EnumT value>
			static inline std::string etos(){
				return etos_compiletime < LastEntry, static_cast<int>(value) >::get();
			}

			//convert EnumT to string at runtime
			static inline std::string etos(EnumT value){
				if (instance().etosmap_.empty()){
					return etos_linear_lookup<LastEntry>(static_cast<int>(value));
				}
				else{
					return instance().etos_map_lookup(value);
				}
			}

			//get int_value of the entry at index with ::value
			//has the same effect as curr_entry(::prev){index}::value
			template<int index>
			struct int_at{
				typedef typename int_at_index<LastEntry, static_cast<int>(num_vals)-1 - index > iai;
				enum { value = iai::value };
			};
		};

#			define IW_ENUM__ID_OP(_, func, elem) func(elem)
#			define IW_ENUM__APPLY_TO_ALL(func, ...)			\
				BOOST_PP_SEQ_FOR_EACH(						\
				IW_ENUM__ID_OP, func,						\
				BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)		\
			)
#			define STATARG(_, func, elem, statArg) func(elem, statArg)

		//Starts enum defintion
#		define IW_ENUM__BEGIN_ENUM_DEF(enum_name)							\
		namespace _named_enum_artifacts{									\
			namespace BOOST_PP_CAT(enum_name, _artifacts){					\
				enum class enum_name;
		//Defines c-string char name[] = "name";
#		define IW_ENUM__DEFINE_ENUM_STRING(name) \
				char name[] = #name;
		//Ends string definition and begins definition of _named_enum_artifacts::enum_name_artifacts::index
#		define IW_ENUM__BEGIN_ENUM_INDEX_DEF \
				enum class index{
		//Defines index
#		define IW_ENUM__DEFINE_ENUM_INDEX(name) \
					name,
		//Ends index definition and typedefs named_enum::enumeration to enumeration for later use
#		define IW_ENUM__DEFINE_ENUM_NAMED_ENUM(enum_name, supply, ...)													\
				};																										\
				typedef ::boost::named_enum::named_enum<enum_name, supply>::gen<__VA_ARGS__>::get enumeration;			\
				enum class enum_name{
		//Defines enum value
#		define IW_ENUM__DEFINE_ENUM_VALUE(name) \
				name = enumeration::int_at<static_cast<int>(index::name)>::value,
		//Ends enum
#		define IW_ENUM__END_ENUM_DEF(enum_name)																			\
				};																										\
			}																											\
		}																												\
		typedef _named_enum_artifacts::BOOST_PP_CAT(enum_name, _artifacts)::enum_name enum_name;						\
		typedef _named_enum_artifacts::BOOST_PP_CAT(enum_name, _artifacts)::enumeration BOOST_PP_CAT(enum_name, _enum);

		//Does the whole enum definition in one go
#		define IW_ENUM_DEFINE_W_SUPPLY(enum_name, supply, ...)				\
		IW_ENUM__BEGIN_ENUM_DEF(enum_name)									\
		IW_ENUM__APPLY_TO_ALL(IW_ENUM__DEFINE_ENUM_STRING, __VA_ARGS__)		\
		IW_ENUM__BEGIN_ENUM_INDEX_DEF										\
		IW_ENUM__APPLY_TO_ALL(IW_ENUM__DEFINE_ENUM_INDEX, __VA_ARGS__)		\
		IW_ENUM__DEFINE_ENUM_NAMED_ENUM(enum_name, supply, __VA_ARGS__)		\
		IW_ENUM__APPLY_TO_ALL(IW_ENUM__DEFINE_ENUM_VALUE, __VA_ARGS__)		\
		IW_ENUM__END_ENUM_DEF(enum_name)

#		define IW_ENUM_DEFINE(enum_name, ...) IW_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::named_enum::supplies::increment, __VA_ARGS__)

#		define IW_ENUM_ARBITRARY_VALUES(...) ::boost::named_enum::supplies::arbitrary<__VA_ARGS__>::values
	}
}

//example for a macro that uses ENUM_DEFINE_W_SUPPLY
#define DEFINE_FLAG_ENUM(enum_name, ...) IW_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::named_enum::supplies::shiftL1, __VA_ARGS__)

//this is enough to define a named macro
IW_ENUM_DEFINE(Zott,
	zero,
	one,
	two,
	three
);

namespace Act{
	DEFINE_FLAG_ENUM(Action,
		jump,
		look,
		move
		);
}

IW_ENUM_DEFINE_W_SUPPLY(Numbers, 
IW_ENUM_ARBITRARY_VALUES(5, 8, 20, 6, 41),
	five,
	eight,
	twenty,
	six,
	fortyone
);

////namespace something{
//	Action ultimately expands to this:
//	namespace _named_enum_artifacts{
//		namespace Action_artifacts{
//			enum class Action;
//			char jump[] = "jump";
//			char look[] = "look";
//			char move[] = "move";
//			enum class index{
//				jump,
//				look,
//				move,
//			};
//			typedef ::boost::named_enum::named_enum<Action, void, ::boost::named_enum::supplies::shiftL1>::gen<jump, look, move>::get enumeration;
//			enum class Action{
//				jump = enumeration::int_at<static_cast<int>(index::jump)>::value,
//				look = enumeration::int_at<static_cast<int>(index::look)>::value,
//				move = enumeration::int_at<static_cast<int>(index::move)>::value,
//			};
//		}
//	}
//	typedef _named_enum_artifacts::Action_artifacts::enumeration Action_enum;
//	typedef _named_enum_artifacts::Action_artifacts::Action Action;
//}

#endif //include guard