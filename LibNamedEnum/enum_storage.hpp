
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ADVANCEDENUM_ENUM_STORAGE_HPP
#define BOOST_ADVANCEDENUM_ENUM_STORAGE_HPP

#include <boost/config.hpp>
#include <string>
#include "Supplies.hpp"

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
		template<typename UnderlyingT = int, template<UnderlyingT> class Supply = supplies::increment<UnderlyingT>::values, typename LastEntry = void>
		class enum_storage{
		public:
			///Used for indexing
			typedef typename std::make_unsigned<UnderlyingT>::type SizeT;
			///Makes UnderlyingT publicly visible
			typedef typename UnderlyingT UnderlyingT;
		private:
			//-------linked list------------
			///value entries represent a value string pair each in a reverse linked list.
			/**The only arguments are the string and previous entry, the value is determined by instantiating
			 * the  Supply template with the value of PrevEntry.
			 * The list has to be reversed to make the definition of enums with 
			 *  BOOST_ADVANCED_ENUM_DEFINE_W_SUPPLY possible.
			*/
			template<char* Name, typename PrevEntry>
			struct value_entry{
				typedef PrevEntry prev;
				const std::string name = Name;
				enum : UnderlyingT{ value = Supply<PrevEntry::value>::next };

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
			template <char* Name>
			struct value_entry < Name, void > {
				typedef void prev;
				const std::string name = Name;
				enum : UnderlyingT{ value = Supply<0>::start };

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
			static enum_storage& instance(){
				static enum_storage instance_;
				return instance_;
			}

			//init method for stoemap
			void init_stoemap(){
				stoemap_.clear();
				LastEntry().insert_into_stoemap(stoemap_);
			}
			///Fast map lookup for etos conversion
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
			///Fast map lookup for etos conversion
			std::string etos_map_lookup(UnderlyingT key){
				try{
					return etosmap_.at(key);
				}
				catch (const std::out_of_range&){
					throw std::invalid_argument(std::to_string(key) + " is not a value in this enum.");
				}
			}

			////------generator------
			///Replaces the last template argument of enum_storage with NewLastEntry
			template<typename NewLastEntry>
			struct with_last{
				typedef enum_storage<UnderlyingT, Supply, NewLastEntry> get;
			};
			

			///Generator for enum_storage, used by gen
			template<typename PrevEntry, char* entry_name, char* ... next_entries>
			struct generator{
				typedef typename enum_storage::template value_entry<entry_name, PrevEntry> entry;
				typedef typename generator<entry, next_entries ...>::enumeration enumeration;
			};
			///End case for generator
			template<typename PrevEntry, char* entry_name>
			struct generator < PrevEntry, entry_name > {
				typedef typename enum_storage::template value_entry<entry_name, PrevEntry> entry;
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

			///Linear lookup for etos conversion, used by etos(UnderlyingT)
			template<typename CurrEntry>
			static std::string etos_linear_lookup(UnderlyingT value){
				if (value == CurrEntry::value)
					return CurrEntry().name;
				else
					return etos_linear_lookup<CurrEntry::prev>(value);
			}
			///Failure case for etos_linear lookup when value is not a value in this enum
			template<>
			static inline std::string etos_linear_lookup<void>(UnderlyingT value){
				throw std::invalid_argument(std::to_string(value) + " is not a value in this enum.");
				return "";
			}
		public:
			///generator to create a enum_storage
			/**like so: 
			 * \code 
			 *     typedef enum_storage<[Supply]>::gen<entry{, entry}>::get myStorage;
			 * \endcode
			*/
			template<char* ... entries>
			struct gen{
				typedef typename generator<void, entries ...>::enumeration get;
			};

			///Number of values the enum has
			enum : SizeT { num_vals = number_of_elements<LastEntry>::value };

			///Initialise lookup maps (not required, but recommended for large enums)
			static void init_lookupmaps(){
				instance().init_etosmap();
				instance().init_stoemap();
			}

			///Convert string to UnderlyingT
			static UnderlyingT stoe(const std::string& name){
				if (instance().stoemap_.empty()){
					return stoe_linear_lookup<LastEntry>(name);
				}
				else{
					return instance().stoe_map_lookup(name);
				}
			}

			///Convert UnderlyingT to string at compiletime
			template<UnderlyingT value>
			static inline std::string etos(){
				return etos_compiletime < LastEntry, static_cast<int>(value) >::get();
			}

			///Convert UnderlyingT to string at runtime
			static inline std::string etos(UnderlyingT value){
				if (instance().etosmap_.empty()){
					return etos_linear_lookup<LastEntry>(value);
				}
				else{
					return instance().etos_map_lookup(value);
				}
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