
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

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
#include "Supplies.hpp"


namespace boost{
	namespace advanced_enum{


		//this class can be typedef-d to offer conversions from and to std::string
		//It is recommended to use the supplied macros for that
		template<typename UnderlyingT = int, template<UnderlyingT> class Supply = supplies::increment<UnderlyingT>::values, typename LastEntry = void>
		class enum_storage{
		public:
			typedef typename std::make_unsigned<UnderlyingT>::type SizeT; //used for indexing and number of elements
			typedef typename UnderlyingT UnderlyingT;
		private:
			////-------linked list------------
			//entry that represents one enum value
			template<const char* Name, typename PrevEntry>
			struct value_entry{
				typedef PrevEntry prev;
				const std::string name = Name;
				enum : UnderlyingT{ value = Supply<PrevEntry::value>::next };

				void insert_into_stoemap(std::map<std::string, UnderlyingT>& map){
					prev().insert_into_stoemap(map);
					map.insert(std::pair<std::string, UnderlyingT>(name, value));
				}

				void insert_into_etosmap(std::map<UnderlyingT, std::string>& map){
					prev().insert_into_etosmap(map);
					map.insert(std::pair<UnderlyingT, std::string>(value, name));
				}
			};

			//specialisation for the first element
			template <const char* Name>
			struct value_entry < Name, void > {
				typedef void prev;
				const std::string name = Name;
				enum : UnderlyingT{ value = Supply<0>::start };

				void insert_into_stoemap(std::map<std::string, UnderlyingT>& map){
					map.insert(std::pair<std::string, UnderlyingT>(name, value));
				}

				void insert_into_etosmap(std::map<UnderlyingT, std::string>& map){
					map.insert(std::pair<UnderlyingT, std::string>(value, name));
				}
			};

			////-----lookup maps--------
			//map for fast lookup of strings
			std::map<std::string, UnderlyingT> stoemap_;
			//map for fast lookup of enum values
			std::map<UnderlyingT, std::string> etosmap_;
				
			//singleton instance
			static enum_storage& instance(){
				static enum_storage instance_;
				return instance_;
			}

			//init method for stoemap
			void init_stoemap(){
				stoemap_.clear();
				LastEntry().insert_into_stoemap(stoemap_);
			}
			//do a lookup
			UnderlyingT stoe_map_lookup(const std::string& key){
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
			std::string etos_map_lookup(UnderlyingT key){
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
				typedef enum_storage<UnderlyingT, Supply, LastEntry2> get;
			};
			//generate enum_storage
			template<typename PrevEntry, const char* entry_name, const char* ... next_entries>
			struct generator{
				typedef typename enum_storage::template value_entry<entry_name, PrevEntry> entry;
				typedef typename generator<entry, next_entries ...>::enumeration enumeration;
			};
			//final case
			template<typename PrevEntry, const char* entry_name>
			struct generator < PrevEntry, entry_name > {
				typedef typename enum_storage::template value_entry<entry_name, PrevEntry> entry;
				typedef typename enum_storage::template with_last<entry>::get enumeration;
			};

			/////-------indexing-------
			//number of elements
			template<typename CurrEntry>
			struct number_of_elements{
				enum : SizeT { value = 1 + number_of_elements<CurrEntry::prev>::value };
			};
			//final case for first element
			template<>
			struct number_of_elements < void > {
				enum : SizeT { value = 0 };
			};

			//like using CurrEntry(::prev){index}::value
			template<typename CurrEntry, typename index>
			struct value_at_index{
				typedef typename CurrEntry::prev prev;
				enum : UnderlyingT { value = value_at_index<prev, std::integral_constant<SizeT, index::value - 1> >::value };
			};
			//final case
			template<typename CurrEntry>
			struct value_at_index < CurrEntry, std::integral_constant<SizeT, 0> > {
				enum : UnderlyingT { value = CurrEntry::value };
			};


			////-----------conversion------------
			//convert string to underlying type at runtime
			template<typename CurrEntry>
			static UnderlyingT stoe_linear_lookup(const std::string& name){
				if (name == CurrEntry().name)
					return CurrEntry::value;
				else
					return stoe_linear_lookup<typename CurrEntry::prev>(name);
			}
			//failure case when CurrEntry is void
			template<>
			static inline UnderlyingT stoe_linear_lookup<void>(const std::string& name){
				throw std::invalid_argument(name + " is not convertible to this enum.");
				return 0;
			}

			//convert underlying type to string at compiletime (only works with literals and constants)
			template<typename CurrEntry, UnderlyingT value, UnderlyingT CurrVal = CurrEntry::value>
			struct etos_compiletime{
				static inline std::string get(){
					return etos_compiletime<CurrEntry::prev, value>::get();
				}
			};
			//success case when value and CurrVal are equal
			template<typename CurrEntry, UnderlyingT value>
			struct etos_compiletime < CurrEntry, value, value > {
				static inline std::string get(){
					return CurrEntry().name;
				}
			};

			//convert int to string at runtime
			template<typename CurrEntry>
			static std::string etos_linear_lookup(UnderlyingT value){
				if (value == CurrEntry::value)
					return CurrEntry().name;
				else
					return etos_linear_lookup<CurrEntry::prev>(value);
			}
			//failure case when CurrEntry is void (which shouldn't ever happen)
			template<>
			static inline std::string etos_linear_lookup<void>(UnderlyingT value){
				throw std::invalid_argument(std::to_string(value) + " is not a value in this enum.");
				return "";
			}
		public:
			//generator to create a enum_storage like so: enum_storage<[Supply]>::gen<entry{, entry}>::get
			template<const char* ... entries>
			struct gen{
				typedef typename generator<void, entries ...>::enumeration get;
			};

			//number of elements
			enum : SizeT { num_vals = number_of_elements<LastEntry>::value };

			//initialise lookup maps (not required, but recommended for large enums)
			static void init_lookupmaps(){
				instance().init_etosmap();
				instance().init_stoemap();
			}

			//convert string to UnderlyingT at runtime
			static UnderlyingT stoe(const std::string& name){
				if (instance().stoemap_.empty()){
					return stoe_linear_lookup<LastEntry>(name);
				}
				else{
					return instance().stoe_map_lookup(name);
				}
			}

			//convert UnderlyingT to string at compiletime
			template<UnderlyingT value>
			static inline std::string etos(){
				return etos_compiletime < LastEntry, static_cast<int>(value) >::get();
			}

			//convert UnderlyingT to string at runtime
			static inline std::string etos(UnderlyingT value){
				if (instance().etosmap_.empty()){
					return etos_linear_lookup<LastEntry>(value);
				}
				else{
					return instance().etos_map_lookup(value);
				}
			}

			//get value of the entry at index with ::value
			//has the same effect as CurrEntry(::prev){index}::value
			template<SizeT index>
			struct value_at{
				typedef typename value_at_index<LastEntry, std::integral_constant<SizeT, num_vals - 1 - index> > vai;
				enum { value = vai::value };
			};
		};

		template<typename EnumStorage, typename ValueT>
		class advanced_enum_base{
		public:
			typedef typename ValueT ValueT;
			typedef typename EnumStorage EnumStorage;
			typedef typename EnumStorage::UnderlyingT UnderlyingT;
		private:
			ValueT value_;
		public:
			//-----construction and assignment-------
			advanced_enum_base(){}
			advanced_enum_base(ValueT value) :
				value_(value)
			{}

			advanced_enum_base& operator=(const advanced_enum_base& rhs){
				value_ = rhs.value_;
				return *this;
			}

			advanced_enum_base& operator=(ValueT rhs){
				value_ = rhs;
				return *this;
			}

			//---------------conversion---------------
			static void init_lookupmaps(){
				EnumStorage::init_lookupmaps();
			}

			explicit advanced_enum_base(int value) :
				value_(static_cast<ValueT>(value))
			{}
			explicit advanced_enum_base(const std::string& name) :
				value_(static_cast<ValueT>(EnumStorage::stoe(name)))
			{}

			explicit operator std::string() const{
				return EnumStorage::etos(value_);
			}

			explicit operator UnderlyingT() const{
				return static_cast<UnderlyingT>(value_);
			}

			//------------comparison---------------
			bool operator ==(const advanced_enum_base& other) const{
				return value_ == other.value_;
			}

			bool operator !=(const advanced_enum_base& other) const{
				return value_ != other.value_;
			}

			bool operator >=(const advanced_enum_base& other) const{
				return value_ >= other.value_;
			}

			bool operator <=(const advanced_enum_base& other) const{
				return value_ <= other.value_;
			}

			bool operator >(const advanced_enum_base& other) const{
				return value_ > other.value_;
			}

			bool operator <(const advanced_enum_base& other) const{
				return value_ < other.value_;
			}

		};

		template<typename ... TemplArgs>
		std::istream& operator >>(std::istream& lhs, advanced_enum_base<TemplArgs ...>& rhs){
			std::string s;
			lhs >> s;
			try{
				rhs = static_cast<advanced_enum_base<TemplArgs ...>>(s);
			}
			catch (const std::invalid_argument&) //rhs stays unchanged when an error occurs
			{}
			return lhs;
		}

		template<typename ... TemplArgs>
		inline std::ostream& operator <<(std::ostream& lhs, advanced_enum_base<TemplArgs ...>& rhs){
			std::string s = static_cast<std::string>(rhs);
			lhs << s;
			return lhs;
		}


		//apply a macro or function to all variadic arguments
#		define BOOST_ADVANCED_ENUM__ID_OP(_, func, elem) func(elem)
#		define BOOST_ADVANCED_ENUM__APPLY_TO_ALL(func, ...)			\
			BOOST_PP_SEQ_FOR_EACH(									\
			BOOST_ADVANCED_ENUM__ID_OP, func,							\
			BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)					\
		)


#		define BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name)				\
		namespace {																\
			namespace _advanced_enum_artifacts{									\
				namespace BOOST_PP_CAT(enum_name,_artifacts){					\

#		define BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING(name)						\
					char name[] = #name;										\

#		define BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(supply, ...)			\
					typedef ::boost::advanced_enum::enum_storage<supply::UnderlyingT, supply::values>::			\
						gen<__VA_ARGS__>::get enum_storage;						\
					enum class index : enum_storage::SizeT{						\

#		define BOOST_ADVANCED_ENUM__DEFINE_INDEX(name)								\
						name,													\

#		define BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION			\
					};															\
					namespace Values{											\
						enum Values{											\

#		define BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE(name)						\
							name = enum_storage::								\
								value_at<static_cast<enum_storage::SizeT>(index::name)>::value,	\

#		define BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)				\
						};														\
					}															\
					typedef ::boost::advanced_enum::advanced_enum_base				\
						<enum_storage, Values::Values> Base;					\
					struct  enum_name : Base {									\

#		define BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE(name)						\
						static const ValueT name = ValueT::name;				\

#		define BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)						\
						enum_name() : Base(){}									\
						enum_name(ValueT v) : Base(v){}							\
						explicit enum_name(UnderlyingT v) : Base(v){}			\
						explicit enum_name(const std::string& s) : Base(s){}	\
					};															\
				}																\
			}																	\
		}																		\
		typedef _advanced_enum_artifacts::BOOST_PP_CAT(enum_name,_artifacts)::		\
			enum_name enum_name												\


		//Does the whole enum definition in one go
#		define BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, supply, ...)							\
		BOOST_ADVANCED_ENUM__BEGIN_DEFINITION(enum_name)											\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_NAME_STRING, __VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__BEGIN_INDEX_DEFINITION(supply, __VA_ARGS__)							\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_INDEX, __VA_ARGS__)				\
		BOOST_ADVANCED_ENUM__BEGIN_VALUES_DEFINITION												\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_VALUES_VALUE,__VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__BEGIN_ENUM_DEFINITION(enum_name)										\
		BOOST_ADVANCED_ENUM__APPLY_TO_ALL(BOOST_ADVANCED_ENUM__DEFINE_ENUM_VALUE, __VA_ARGS__)		\
		BOOST_ADVANCED_ENUM__END_DEFINITION(enum_name)												\

#		define BOOST_ADVANCED_ENUM_DEFINE(enum_name, ...) BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY(enum_name, ::boost::advanced_enum::supplies::increment<int>, __VA_ARGS__)

#		define BOOST_ADVANCED_ENUM_ARBITRARY_VALUES(...) ::boost::advanced_enum::supplies::arbitrary<__VA_ARGS__>
	}
}

//uncomment to test 

//Action ultimately expands to this:
//namespace something{
//	namespace {
//		namespace _advanced_enum_artifacts{
//			namespace Action_artifacts{
//				char jump[] = "jump";
//				char look[] = "look";
//				char move[] = "move";
//				enum class index{
//					jump,
//					look,
//					move,
//				};
//				typedef ::boost::advanced_enum::enum_storage<int, ::boost::advanced_enum::supplies::shiftL1<int>::values>::gen<jump, look, move>::get enum_storage;
//				namespace Values{
//					enum Values{
//						jump = enum_storage::int_at<static_cast<int>(index::jump)>::value,
//						look = enum_storage::int_at<static_cast<int>(index::look)>::value,
//						move = enum_storage::int_at<static_cast<int>(index::move)>::value,
//					};
//				}
//				typedef ::boost::advanced_enum::advanced_enum_base <enum_storage, Values::Values> Base;
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
//	typedef _advanced_enum_artifacts::Action_artifacts::Action Action;
//}

#endif //include guard