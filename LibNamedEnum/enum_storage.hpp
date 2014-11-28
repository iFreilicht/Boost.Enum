
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ADVANCEDENUM_ENUM_STORAGE2_HPP
#define BOOST_ADVANCEDENUM_ENUM_STORAGE2_HPP

#include <boost/config.hpp>
#include <string>
#include "supplies.hpp"
#include "supply_selector.hpp"
#include "options.h"
#include "etos_impl.hpp"
#include "stoe_impl.hpp"
#include "instance_impl.h"

#ifdef BOOST_MSVC
#pragma warning(disable : 4503)
#endif


namespace boost{
	namespace advanced_enum{

		///enum_storage is a compile-time container for enumeration values and their corresponding string.
		/**The container is implemented as a reverse linked list, starting at the last entry.
		 * Besides containing all value string pairs of an enumeration, it provides methods
		 * for conversion and initialisation of an advanced_enum and is therefore its
		 * implementation.
		 * The conversions are abbreviated with stoe (string to enum) and etos (enum to string).
		 * For the most part, it consists only of constants and types, but the two std::maps
		 * used for lookups can only accessed via the instance() member function.
		 * There is generally no need to use this class directly.
		 * For instantiating the enum_storage template, use the following syntax:
		 * \code 
		 *     typedef enum_storage<[underlying type][, supply]>::gen<{entries}>::get myStorage_t;
		 * \endcode
		*/
		template<
			typename options = Options<>, 
			typename LastEntry = void>
		class enum_storage{
		public:
			typedef typename options::UnderlyingT UnderlyingT;
			///Used for indexing
			typedef typename std::make_unsigned<UnderlyingT>::type SizeT;

			typedef LastEntry LastEntry;
		private:
			//-------linked list------------
			///value entries represent a value string pair each in a reverse linked list.
			/**The only arguments are the string and previous entry, the value is determined by instantiating
			 * the  Supply template with the value of PrevEntry.
			 * The list has to be reversed to make the definition of enums with 
			 *  BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY possible.
			*/
			template<typename NameValuePair, typename PrevEntry>
			struct value_entry{
				typedef PrevEntry prev;
				const std::string name = NameValuePair::name;
				enum : UnderlyingT{ value = NameValuePair::value };

				///Inserts string value pair into map
				/**The same is done recursively for PrevEntry
				*/
				void insert_into_stoemap(std::map<std::string, UnderlyingT>& map){
					prev().insert_into_stoemap(map);
					map.insert(std::pair<std::string, UnderlyingT>(name, value));
				}

				///Inserts value string pair into map
				/**The same is done recursively for PrevEntry
				*/
				void insert_into_etosmap(std::map<UnderlyingT, std::string>& map){
					prev().insert_into_etosmap(map);
					map.insert(std::pair<UnderlyingT, std::string>(value, name));
				}
			};

			///specialisation for value_entry that represents the first entry in the linked list
			template <typename NameValuePair>
			struct value_entry < NameValuePair, void > {
				typedef void prev;
				const std::string name = NameValuePair::name;
				enum : UnderlyingT{ value = NameValuePair::value };

				///\sa value_entry::insert_into_stoemap 
				void insert_into_stoemap(std::map<std::string, UnderlyingT>& map){
					map.insert(std::pair<std::string, UnderlyingT>(name, value));
				}

				///\sa value_entry::insert_into_etosmap
				void insert_into_etosmap(std::map<UnderlyingT, std::string>& map){
					map.insert(std::pair<UnderlyingT, std::string>(value, name));
				}
			};

			//-----lookup maps--------
			///Map for fast lookup of values with strings
			std::map<std::string, UnderlyingT> stoemap_;
			///Map for fast lookup of strings with values
			std::map<UnderlyingT, std::string> etosmap_;

			///Singleton instance
			typedef instance_impl<enum_storage<options, LastEntry>, options::map_lookup> InstanceImpl;

			static enum_storage& instance(){
				static enum_storage instance_ = InstanceImpl::newInstance();
				return instance_;
			}

			//init method for stoemap
			void init_stoemap(){
				stoemap_.clear();
				LastEntry().insert_into_stoemap(stoemap_);
			}
			
			//init method for etosmap
			void init_etosmap(){
				etosmap_.clear();
				LastEntry().insert_into_etosmap(etosmap_);
			}

			////------generator------
			///Replaces the last template argument of enum_storage with NewLastEntry
			template<typename NewLastEntry>
			struct with_last{
				typedef enum_storage<options, NewLastEntry> get;
			};
			

			///Generator for enum_storage, used by gen
			template<typename PrevEntry, typename entry_name, typename ... next_entries>
			struct generator{
				typedef typename enum_storage::template value_entry<entry_name, PrevEntry> entry;
				typedef typename generator<entry, next_entries ...>::enumeration enumeration;
			};
			///End case for generator
			template<typename PrevEntry, typename entry_name>
			struct generator < PrevEntry, entry_name> {
				typedef typename enum_storage::template value_entry<entry_name, PrevEntry> entry;
				typedef typename enum_storage::template with_last<entry>::get enumeration;
			};

			template<typename PrevEntry>
			struct generator < PrevEntry, void > {
				typedef PrevEntry entry;
				typedef typename enum_storage::template with_last<entry>::get enumeration;
			};


			/////-------indexing-------
			///Number of elements of the linked list, used by num_vals
			template<typename CurrEntry>
			struct number_of_elements{
				enum : SizeT { value = 1 + number_of_elements<CurrEntry::prev>::value };
			};
			///End case for  number_of_elements
			template<>
			struct number_of_elements < void > {
				enum : SizeT { value = 0 };
			};

			///Accessor implementation, used by value_at
			template<typename CurrEntry, typename index>
			struct value_at_index{
				typedef typename CurrEntry::prev prev;
				enum : UnderlyingT { value = value_at_index<prev, std::integral_constant<SizeT, index::value - 1> >::value };
			};
			///End case for value_at_index
			template<typename CurrEntry>
			struct value_at_index < CurrEntry, std::integral_constant<SizeT, 0> > {
				enum : UnderlyingT { value = CurrEntry::value };
			};


			////-----------conversion------------
			///Linear lookup for stoe conversion, used by stoe(const std::string&)
			template<typename CurrEntry>
			static UnderlyingT stoe_linear_lookup(const std::string& name){
				if (name == CurrEntry().name)
					return CurrEntry::value;
				else
					return stoe_linear_lookup<typename CurrEntry::prev>(name);
			}
			///Failure case for stoe_linear_lookup when name is not the name of a value
			template<>
			static inline UnderlyingT stoe_linear_lookup<void>(const std::string& name){
				throw std::invalid_argument(name + " is not convertible to this enum.");
				return 0;
			}

			///Compile time etos conversion, used by etos<UnderlyingT>
			template<typename CurrEntry, UnderlyingT value, UnderlyingT CurrVal = CurrEntry::value>
			struct etos_compiletime{
				static inline std::string get(){
					return etos_compiletime<CurrEntry::prev, value>::get();
				}
			};
			///End case for etos_compiletime
			template<typename CurrEntry, UnderlyingT value>
			struct etos_compiletime < CurrEntry, value, value > {
				static inline std::string get(){
					return CurrEntry().name;
				}
			};

		public:
			///generator to create a enum_storage
			/**like so: 
			 * \code 
			 *     typedef enum_storage<[Supply]>::gen<entry{, entry}>::get myStorage;
			 * \endcode
			 * \note It is required to make the last argument void, which is needed by certain macros
			*/
			template<typename ... entries>
			struct gen{
				typedef typename generator<void, entries ...>::enumeration get;
			};

			///Number of values the enum has
			enum : SizeT { num_vals = number_of_elements<LastEntry>::value };

			///Initialise lookup maps (not required, but recommended for large enums)
			static void init_lookupmaps(){
				instance().init_lookupmaps_non_static();
			}

			void init_lookupmaps_non_static(){
				init_etosmap();
				init_stoemap();
			}
			


			///Convert string to UnderlyingT
			static UnderlyingT stoe(const std::string& name){
				return stoe_impl<options, enum_storage<options, LastEntry> >::f(name);
			}

			///Convert UnderlyingT to string at compiletime
			template<UnderlyingT value>
			static inline std::string etos(){
				return etos_compiletime < LastEntry, value >::get();
			}

			///Convert UnderlyingT to string at runtime
			static inline std::string etos(UnderlyingT value){
				return etos_impl<options, enum_storage<options, LastEntry> >::f(value);
			}

			///Get value of the entry at index with ::value
			/**has the same effect as CurrEntry(::prev){index}::value
			*/
			template<SizeT index>
			struct value_at{
				typedef typename value_at_index<LastEntry, std::integral_constant<SizeT, num_vals - 1 - index> > vai;
				enum { value = vai::value };
			};
		};

	}
}

#endif //include guard