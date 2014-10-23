
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
#include <istream>


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
		//It is recommended to use the supplied macros for that
		template<template<int> class Supply = supplies::increment, typename LastEntry = void>
		class named_enum{
		private:
			////-------linked list------------
			//entry that represents one enum value
			template<const char* Name, typename PrevEntry>
			struct value_entry{
				typedef PrevEntry prev;
				const std::string name = Name;
				enum{ int_value = Supply<PrevEntry::int_value>::value };

				void insert_into_stoemap(std::map<std::string, int>& map){
					prev().insert_into_stoemap(map);
					map.insert(std::pair<std::string, int>(name, int_value));
				}

				void insert_into_etosmap(std::map<int, std::string>& map){
					prev().insert_into_etosmap(map);
					map.insert(std::pair<int, std::string>(int_value, name));
				}
			};

			//specialisation for the first element
			template <const char* Name>
			struct value_entry < Name, void > {
				typedef void prev;
				const std::string name = Name;
				enum{ int_value = Supply<0>::start };

				void insert_into_stoemap(std::map<std::string, int>& map){
					map.insert(std::pair<std::string, int>(name, int_value));
				}

				void insert_into_etosmap(std::map<int, std::string>& map){
					map.insert(std::pair<int, std::string>(int_value, name));
				}
			};

			////-----lookup maps--------
			//map for fast lookup of strings
			std::map<std::string, int> stoemap_;
			//map for fast lookup of enum values
			std::map<int, std::string> etosmap_;
				
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
			int stoe_map_lookup(const std::string& key){
				try{
					return stoemap_.at(key);
				}
				catch (const std::out_of_range&){
					throw std::invalid_argument(key + " is not convertible to this enum.");
				}
			}

			//init method for etosmap
			void init_etosmap(){
				etosmap_.clear();
				LastEntry().insert_into_etosmap(etosmap_);
			}
			//do a lookup
			std::string etos_map_lookup(int key){
				try{
					return etosmap_.at(key);
				}
				catch (const std::out_of_range&){
					throw std::invalid_argument(std::to_string(key) + " is not a value in this enum.");
				}
			}

			////------generator------
			//type with same arguments except LastEntry
			template<typename LastEntry2>
			struct with_last{
				typedef named_enum<Supply, LastEntry2> get;
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
			//convert string to int at runtime
			template<typename curr_entry>
			static int stoe_linear_lookup(const std::string& name){
				if (name == curr_entry().name)
					return curr_entry::int_value;
				else
					return stoe_linear_lookup<typename curr_entry::prev>(name);
			}
			//failure case when curr_entry is void
			template<>
			static inline int stoe_linear_lookup<void>(const std::string& name){
				throw std::invalid_argument(name + " is not convertible to this enum.");
				return 0;
			}

			//convert int to string at compiletime (only works with literals and constants)
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

			//convert int to string at runtime
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
				throw std::invalid_argument(std::to_string(value) + " is not a value in this enum.");
				return "";
			}
		public:
			//generator to create a named_enum like so: named_enum<[Supply]>::gen<entry{, entry}>::get
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

			//convert string to int at runtime
			static int stoe(const std::string& name){
				if (instance().stoemap_.empty()){
					return stoe_linear_lookup<LastEntry>(name);
				}
				else{
					return instance().stoe_map_lookup(name);
				}
			}

			//convert int to string at compiletime
			template<int value>
			static inline std::string etos(){
				return etos_compiletime < LastEntry, static_cast<int>(value) >::get();
			}

			//convert int to string at runtime
			static inline std::string etos(int value){
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

		template<typename EnumStorage, typename ValueType>
		class named_enum_base{
		public:
			typedef typename ValueType ValueT;
			typedef typename EnumStorage EnumStorage;
		private:
			ValueT value_;
		public:
			named_enum_base(ValueT value) :
				value_(value)
			{}
			explicit named_enum_base(int value) :
				value_(static_cast<ValueT>(value))
			{}
			explicit named_enum_base(const std::string& name) :
				value_(static_cast<ValueT>(EnumStorage::stoe(name)))
			{}

			named_enum_base& operator=(const named_enum_base& rhs){
				value_ = rhs.value_;
				return *this;
			}

			named_enum_base& operator=(ValueT rhs){
				value_ = rhs;
				return *this;
			}

			explicit operator int(){
				return value_;
			}
		};

		template<typename ... TempArgs>
		std::istream& operator >>(std::istream& lhs, named_enum_base<TempArgs ...>& rhs){
			std::string s;
			lhs >> s;
			try{
				rhs = static_cast<named_enum_base<TempArgs ...>>(s);
			}
			catch (const std::invalid_argument&) //rhs stays unchanged when an error occurs
			{}
			return lhs;
		}

		template<typename ... TempArgs>
		inline std::ostream& operator <<(std::ostream& lhs, named_enum_base<TempArgs ...>& rhs){
			std::string s = named_enum_base < TempArgs ... > ::EnumStorage::etos(static_cast<int>(rhs));
			lhs << s;
			return lhs;
		}



		//apply a macro or function to all variadic arguments
#		define BOOST_NAMED_ENUM__ID_OP(_, func, elem) func(elem)
#		define BOOST_NAMED_ENUM__APPLY_TO_ALL(func, ...)			\
			BOOST_PP_SEQ_FOR_EACH(									\
			BOOST_NAMED_ENUM__ID_OP, func,							\
			BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)					\
		)


#		define BOOST_NAMED_ENUM__BEGIN_DEFINITION(enum_name)				\
		namespace {																\
			namespace _named_enum_artifacts{									\
				namespace BOOST_PP_CAT(enum_name,_artifacts){					\

#		define BOOST_NAMED_ENUM__DEFINE_NAME_STRING(name)						\
					char name[] = #name;										\

#		define BOOST_NAMED_ENUM__BEGIN_INDEX_DEFINITION							\
					enum class index{											\

#		define BOOST_NAMED_ENUM__DEFINE_INDEX(name)								\
						name,													\

#		define BOOST_NAMED_ENUM__BEGIN_VALUES_DEFINITION(supply, ...)			\
					};															\
					typedef ::boost::named_enum::named_enum<supply>::			\
						gen<__VA_ARGS__>::get name_storage;						\
					namespace Values{											\
						enum Values{											\

#		define BOOST_NAMED_ENUM__DEFINE_VALUES_VALUE(name)						\
							name = name_storage::								\
								int_at<static_cast<int>(index::name)>::value,	\

#		define BOOST_NAMED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)				\
						};														\
					}															\
					typedef ::boost::named_enum::named_enum_base				\
						<name_storage, Values::Values> Base;					\
					struct  enum_name : Base {									\

#		define BOOST_NAMED_ENUM__DEFINE_ENUM_VALUE(name)						\
						static const ValueT name = ValueT::name;				\

#		define BOOST_NAMED_ENUM__END_DEFINITION(enum_name)						\
						enum_name(ValueT v) : Base(v){}							\
						explicit enum_name(int v) : Base(v){}					\
						explicit enum_name(const std::string& s) : Base(s){}	\
					};															\
				}																\
			}																	\
		}																		\
		typedef _named_enum_artifacts::BOOST_PP_CAT(enum_name,_artifacts)::		\
			enum_name enum_name;												\


		//Does the whole enum definition in one go
#		define BOOST_NAMED_ENUM_DEFINE_W_SUPPLY(enum_name, supply, ...)							\
		BOOST_NAMED_ENUM__BEGIN_DEFINITION(enum_name)											\
		BOOST_NAMED_ENUM__APPLY_TO_ALL(BOOST_NAMED_ENUM__DEFINE_NAME_STRING, __VA_ARGS__)		\
		BOOST_NAMED_ENUM__BEGIN_INDEX_DEFINITION												\
		BOOST_NAMED_ENUM__APPLY_TO_ALL(BOOST_NAMED_ENUM__DEFINE_INDEX, __VA_ARGS__)				\
		BOOST_NAMED_ENUM__BEGIN_VALUES_DEFINITION(supply, __VA_ARGS__)							\
		BOOST_NAMED_ENUM__APPLY_TO_ALL(BOOST_NAMED_ENUM__DEFINE_VALUES_VALUE,__VA_ARGS__)		\
		BOOST_NAMED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)										\
		BOOST_NAMED_ENUM__APPLY_TO_ALL(BOOST_NAMED_ENUM__DEFINE_ENUM_VALUE, __VA_ARGS__)		\
		BOOST_NAMED_ENUM__END_DEFINITION(enum_name)												\

#		define BOOST_NAMED_ENUM_DEFINE(enum_name, ...) BOOST_NAMED_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::named_enum::supplies::increment, __VA_ARGS__)

#		define BOOST_NAMED_ENUM_ARBITRARY_VALUES(...) ::boost::named_enum::supplies::arbitrary<__VA_ARGS__>::values
	}
}

//uncomment to test 

//Action ultimately expands to this:
//namespace something{
//	namespace {
//		namespace _named_enum_artifacts{
//			namespace Action_artifacts{
//				char jump[] = "jump";
//				char look[] = "look";
//				char move[] = "move";
//				enum class index{
//					jump,
//					look,
//					move,
//				};
//				typedef ::boost::named_enum::named_enum<::boost::named_enum::supplies::shiftL1>::gen<jump, look, move>::get name_storage;
//				namespace Values{
//					enum Values{
//						jump = name_storage::int_at<static_cast<int>(index::jump)>::value,
//						look = name_storage::int_at<static_cast<int>(index::look)>::value,
//						move = name_storage::int_at<static_cast<int>(index::move)>::value,
//					};
//				}
//				typedef ::boost::named_enum::named_enum_base <name_storage, Values::Values> Base;
//				struct Action :  Base {
//					static const ValueT jump = ValueT::jump;
//					static const ValueT look = ValueT::look;
//					static const ValueT move = ValueT::move;
//					Action(ValueT v) : Base(v){}
//					explicit Action(int v) : Base(v){}
//					explicit Action(const std::string& s) : Base(s){}
//				};
//			}
//		}
//	}
//	typedef _named_enum_artifacts::Action_artifacts::Action Action;
//}

#endif //include guard