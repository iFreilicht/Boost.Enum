
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_ENUM_IG_STORAGE_HPP
#define BOOST_ENUM_IG_STORAGE_HPP

#include <boost/config.hpp>
#include <string>
#include <map>
#include <vector>
#include <boost/enum/options/supplies.hpp>
#include <boost/enum/options/supply_selector.hpp>
#include <boost/enum/options/options.hpp>

#ifdef BOOST_MSVC
#pragma warning(disable : 4503)
#endif


namespace boost{
	namespace enum_{

		///storage is a compile-time container for enumeration values and their corresponding string.
		/**The container is implemented as a reverse linked list, starting at the last entry.
		 * Besides containing all value string pairs of an enumeration, it provides methods
		 * for conversion and initialisation of an enum and is therefore its
		 * implementation.
		 * The conversions are abbreviated with stoe (string to enum) and etos (enum to string).
		 * For the most part, it consists only of constants and types, but the two std::maps
		 * used for lookups can only accessed via the instance() member function.
		 * There is generally no need to use this class directly.
		 * For instantiating the storage template, use the following syntax:
		 * \code 
		 *     typedef storage<[underlying type][, supply]>::gen<{entries}>::get myStorage_t;
		 * \endcode
		*/
		template<
			typename Options = options<>, 
			typename LastEntry = void>
		class storage{
		public:
			typedef typename Options::UnderlyingT UnderlyingT;
			///Used for indexing
			typedef typename std::make_unsigned<UnderlyingT>::type SizeT;
			
			typedef typename Options::StringT StringT;

			typedef LastEntry LastEntry;
		private:
			//-------linked list------------
			///value entries represent a value string pair each in a reverse linked list.
			/**The only arguments are the string and previous entry, the value is determined by instantiating
			 * the  Supply template with the value of PrevEntry.
			 * The list has to be reversed to make the definition of enums with 
			 *  BOOST_ENUM_DEFINE_W_SUPPLY possible.
			*/
			template<typename NameValuePair, typename PrevEntry>
			struct value_entry{
				typedef PrevEntry prev;
				const std::string name = NameValuePair::name;
				enum : UnderlyingT{ value = NameValuePair::value };

				///Inserts the value into vec
				static void insert_into_valuevec(std::vector<UnderlyingT>& vec){
					prev::insert_into_valuevec(vec);
					vec.push_back(value);
				}

				///Inserts string value pair into map
				/**The same is done recursively for PrevEntry
				*/
				void insert_into_stoemap(std::map<std::string, UnderlyingT>& map) const{
					prev().insert_into_stoemap(map);
					map.insert(std::pair<std::string, UnderlyingT>(name, value));
				}

				///Inserts value string pair into map
				/**The same is done recursively for PrevEntry
				*/
				void insert_into_etosmap(std::map<UnderlyingT, std::string>& map) const{
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

				///\sa value_entry::insert_into_valuevec
				static void insert_into_valuevec(std::vector<UnderlyingT>& vec){
					vec.push_back(value);
				}

				///\sa value_entry::insert_into_stoemap 
				void insert_into_stoemap(std::map<std::string, UnderlyingT>& map) const{
					map.insert(std::pair<std::string, UnderlyingT>(name, value));
				}

				///\sa value_entry::insert_into_etosmap
				void insert_into_etosmap(std::map<UnderlyingT, std::string>& map) const{
					map.insert(std::pair<UnderlyingT, std::string>(value, name));
				}
			};

			//-----iteration----------
			///Vector for iteration through all possible values
			std::vector<UnderlyingT> valuevec_;

			void init_valuevec(){
				valuevec_.clear();
				valuevec_.reserve(num_vals);
				LastEntry::insert_into_valuevec(valuevec_);
			}

			//-----lookup maps--------
			///Map for fast lookup of values with strings
			std::map<std::string, UnderlyingT> stoemap_;
			///Map for fast lookup of strings with values
			std::map<UnderlyingT, std::string> etosmap_;

			///Singleton instance
			template<bool map_lookup>
			class instance_impl{
				template<bool map_lookup>
				struct newInstance;

				template<>
				struct newInstance<false>{
					static storage get(){
						storage storage{};
						storage.init_valuevec();
						return storage;
					}
				};

				template<>
				struct newInstance<true>{
					static storage get(){
						storage storage{};
						storage.init_lookupmaps_non_static();
						storage.init_valuevec();
						return storage;
					}
				};
			public:
				static storage get(){
					return newInstance<map_lookup>::get();
				}
			};

			typedef instance_impl<Options::map_lookup> InstanceImpl;

			static storage& instance(){
				static storage instance_ = InstanceImpl::get();
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

			//init method for both
			void init_lookupmaps_non_static(){
				init_etosmap();
				init_stoemap();
			}

			////------generator------
			///Replaces the last template argument of storage with NewLastEntry
			template<typename NewLastEntry>
			struct with_last{
				typedef storage<Options, NewLastEntry> get;
			};
			

			///Generator for storage, used by gen
			template<typename PrevEntry, typename entry_name, typename ... next_entries>
			struct generator{
				typedef typename storage::template value_entry<entry_name, PrevEntry> entry;
				typedef typename generator<entry, next_entries ...>::enumeration enumeration;
			};
			///End case for generator
			template<typename PrevEntry, typename entry_name>
			struct generator < PrevEntry, entry_name> {
				typedef typename storage::template value_entry<entry_name, PrevEntry> entry;
				typedef typename storage::template with_last<entry>::get enumeration;
			};

			template<typename PrevEntry>
			struct generator < PrevEntry, void > {
				typedef PrevEntry entry;
				typedef typename storage::template with_last<entry>::get enumeration;
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
			class stoe_impl{
				//linear lookup
				template<typename CurrEntry>
				static UnderlyingT linear_lookup(const StringT& name){
					if (name == CurrEntry().name)
						return CurrEntry::value;
					else
						return linear_lookup<typename CurrEntry::prev>(name);
				}
				///Failure case when name is not the name of a value
				template<>
				static inline UnderlyingT linear_lookup<void>(const std::string& name){
					throw std::invalid_argument(name + " is not convertible to this enum.");
					return 0;
				}

				//map_lookup
				static UnderlyingT map_lookup(const StringT& name){
					try{
						return instance().stoemap_.at(name);
					}
					catch (const std::out_of_range&){
						throw std::invalid_argument(name + " is not convertible to this enum.");
					}
				}

				//lookup
				template<bool Map_lookup>
				static UnderlyingT lookup(const StringT& name);

				template<>
				static inline UnderlyingT lookup<false>(const StringT& name){
					return linear_lookup<LastEntry>(name);
				}

				template<>
				static inline UnderlyingT lookup<true>(const StringT& name){
					return map_lookup(name);
				}

				//impl_f
				template<bool Roundtrip, bool Is_flag, bool Map_lookup>
				struct impl_f;

				template<bool Map_lookup>
				struct impl_f<false, false, Map_lookup>{
					static inline UnderlyingT exec(const StringT& name){
						return lookup<Map_lookup>(name);
					}
				};

				template<bool Map_lookup>
				struct impl_f<true, false, Map_lookup>{
					static inline UnderlyingT exec(const StringT& name){
						UnderlyingT ret;
						try{
							ret = lookup<Map_lookup>(name);
						}
						catch (const std::invalid_argument&){
							ret = std::stoi(name);
						}
						return ret;
					}
				};

				template<bool Map_lookup>
				struct impl_f<true, true, Map_lookup>{
					static inline UnderlyingT exec(const StringT& name){
						static StringT::size_type valBegin;
						static StringT::size_type valEnd;
						valBegin = 0;
						UnderlyingT val = 0;
						while (true){
							valEnd = name.find_first_of('|', valBegin);
							val |= lookup<Map_lookup>(name.substr(valBegin,valEnd));
							if (valEnd == StringT::npos){
								break;
							}
							valBegin = valEnd + 1;
						}
						return val;
					}
				};

			public:
				static inline UnderlyingT f(const StringT& name){
					return impl_f < Options::roundtrip, Options::is_flag, Options::map_lookup >::exec(name);
				}
			};

			class etos_impl{
				//linear_lookup
				template<typename CurrEntry>
				static StringT linear_lookup(UnderlyingT value){
					if (value == CurrEntry::value)
						return CurrEntry().name;
					else
						return linear_lookup<CurrEntry::prev>(value);
				}

				template<>
				static inline StringT linear_lookup<void>(UnderlyingT value){
					throw std::invalid_argument(std::to_string(value) + " is not a value in this enum.");
					return "";
				}

				//map_lookup
				static inline StringT map_lookup(UnderlyingT key){
					try{
						return instance().etosmap_.at(key);
					}
					catch (const std::out_of_range&){
						throw std::invalid_argument(std::to_string(key) + " is not a value in this enum.");
					}
				}

				//lookup
				template<bool Map_lookup>
				static inline StringT lookup(UnderlyingT val);

				template<>
				static inline StringT lookup<false>(UnderlyingT val){
					return linear_lookup<LastEntry>(val);
				}

				template<>
				static inline StringT lookup<true>(UnderlyingT val){
					return map_lookup(val);
				}


				//impl_f
				template<bool Roundtrip, bool Is_Flag, bool Map_lookup>
				struct impl_f{
					static inline StringT exec(UnderlyingT val);
				};

				template<bool Map_lookup>
				struct impl_f < false, false, Map_lookup > {
					static inline StringT exec(UnderlyingT val){
						return lookup<Map_lookup>(val);
					}
				};

				template<bool Map_lookup>
				struct impl_f < true, false, Map_lookup > {
					static inline StringT exec(UnderlyingT val){
						StringT ret{};
						try{
							ret = lookup<Map_lookup>(val);
						}
						catch (const std::invalid_argument&){
							ret = std::to_string(val);
						}
						return ret;
					}
				};

				template<bool Map_lookup>
				struct impl_f < true, true, Map_lookup > {
					static inline StringT exec(UnderlyingT val){
						static UnderlyingT currFlag;
						StringT ret{};
						for (UnderlyingT maskval : valuevec()){
							currFlag = val & maskval;
							if (currFlag != 0){
								ret.append(lookup<Map_lookup>(currFlag));
								ret.push_back('|');
							}
						}
						ret.pop_back();
						return ret;
					}
				};
			public:
				static inline StringT f(UnderlyingT val){
					return impl_f < Options::roundtrip, Options::is_flag, Options::map_lookup >::exec(val);
				}
			};

			class has_val_impl{
				//linear_lookup
				template<typename CurrEntry>
				static bool linear_search(UnderlyingT value){
					if (value == CurrEntry::value)
						return true;
					else
						return linear_search<CurrEntry::prev>(value);
				}

				template<>
				static inline bool linear_search<void>(UnderlyingT value){
					return false;
				}

				//map_lookup
				static inline bool map_search(UnderlyingT key){
					return instance().etosmap_.find(key) != instance().etosmap_.end();
				}


				template<bool Map_lookup>
				struct impl_f;

				template<>
				struct impl_f < false > {
					static inline bool exec(UnderlyingT value){
						return linear_search<LastEntry>(value);
					}
				};

				template<>
				struct impl_f < true > {
					static inline bool exec(UnderlyingT value){
						return map_search(value);
					}
				};
			public:
				static inline bool f(UnderlyingT value){
					return impl_f<Options::map_lookup>::exec(value);
				}
			};

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
			///generator to create a storage
			/**like so: 
			 * \code 
			 *     typedef storage<[Supply]>::gen<entry{, entry}>::get myStorage;
			 * \endcode
			 * \note It is required to make the last argument void, which is needed by certain macros
			*/
			template<typename ... entries>
			struct gen{
				typedef typename generator<void, entries ...>::enumeration get;
			};

			///Number of values the enum has
			enum : SizeT { num_vals = number_of_elements<LastEntry>::value };

			/////Initialise lookup maps (not required, but recommended for large enums)
			//static void init_lookupmaps(){
			//	instance().init_lookupmaps_non_static();
			//}

			///Convert string to UnderlyingT
			static inline UnderlyingT stoe(const std::string& name){
				return stoe_impl::f(name);
			}

			///Convert UnderlyingT to string at compiletime
			template<UnderlyingT value>
			static inline std::string etos(){
				return etos_compiletime < LastEntry, value >::get();
			}

			///Convert UnderlyingT to string at runtime
			static inline std::string etos(UnderlyingT value){
				return etos_impl::f(value);
			}

			///Check whether a value exists in the enumeration
			static inline bool has_value(UnderlyingT value){
				return has_val_impl::f(value);
			}

			static inline const std::vector<UnderlyingT>& valuevec(){
				return instance().valuevec_;
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