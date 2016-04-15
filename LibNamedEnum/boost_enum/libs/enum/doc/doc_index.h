
//          Copyright Felix Uhl 2014
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


/*! \mainpage
	\tableofcontents
	\section intro_sec Introduction
	Boost.Enum is a header-only library that allows you to enhance the functionality of scoped enumerations (unscoped in progress)
	at your discretion. A few features are:

	- String conversion: convert an enumerator not only to its underlying value but also to its actual name
	- Binary flag enums: define full-featured binary flags with ease, readable string output included
	- Runtime value checks: allow or disallow only defined values to be assingned to a variable
	- Ordering control: allow or disallow ordering for your enumerators
	- Generation modification: change the conventions by which values for enumerators are chosen

	Boost.Enum isn't better than enumerations in every way, but it offers features that the stock implementations don't.
	
	




	\section important_files Important Files
	The most important files are:
	- define.hpp
	- adapt.hpp

	\section test Test
	boost::enum_::options
	boost::enum_::adapt_options

	\section Quickstart

	To use Boost.Enum, change the definition of an enum from this

	\code
		enum class Zott{
			zero,
			one,
			two,
			ten = 10
		};
	\endcode

	to this.

	\code
		#include <boost/enum/define.hpp>

		BOOST_ENUM_DEFINE(Zott,
			(zero)
			(one)
			(two)
			(ten, (10))
		)
	\endcode

	For scoped enumerations, this is a non-breaking change, so you can still do all of the following the same way.
	
	Defining variables and assigning values.
	\code
		Zott var = Zott::one;
	\endcode

	Converting from or to int.
	\code
		Zott var = static_cast<Zott>(1);
		int val = static_cast<int>(var);
	\endcode

	Writing the underlying value to a stream.
	\code
	std::out << static_cast<int>(var);
	\endcode

	Converting to the string representation of the underlying value.
	\code
	std::string str = static_cast<std::string>(static_cast<int>(var));
	\endcode

	Additionally, you can now also do the following things.

	Convert to and from std::string.
	\code
		Zott var = static_cast<Zott>("one");
		std::string str = static_cast<std::string>(var);
	\endcode

	Read and write from and to streams.
	\code
		std::cin >> var;	//can take values or names
		std::out << var;	//will output names
	\endcode








	\section Concepts


	\subsection Define Definition of new enums

	Boost.Enums can be used just like regular scoped enumerations.
	Normally a scoped enumeration would be defined like this:

	\code
		enum class Zott{
			zero,
			one,
			two,
			ten = 10
		};
	\endcode

	With Boost.Enum, you do the following:

	\code
		#include <boost/enum/define.hpp>

		BOOST_ENUM_DEFINE(Zott,
			(zero)
			(one)
			(two)
			(ten, (10))
		)
	\endcode

	While it looks a bit strange at first, the uses of this will become apparent later on.
	Above, a new enum was defined using one of the DEFINE macros.






	\subsection Adapt Adaptation of existing enums

	If there is an enumeration that already exists and can't be changed, i.e. because it is part of a library,
	it is also possible to adapt that enum to add some of the features in Boost.Enum onto it by
	using an ADAPT macro.
	
	\code
		//zott.h
		enum class Zott{
			zero,
			one,
			two,
			ten = 10
		};

		//myheader.h
		#include <boost/enum/adapt.hpp>
		#include "zott.h"

		BOOST_ENUM_ADAPT(Zott,
			(zero)
			(one)
			(two)
			(ten)
		)
	\endcode

	Notice how the value of Zott::ten doesn't have to be specified again.






	\subsection Strings String-Conversion

	One of the big features of Boost.Enum is the conversion of enumeration values to
	a string representation of the enumerators name:

	\code
		Zott zott = Zott::one;
		std::string str = static_cast<std::string>(zott);
		std::cout << str;
	\endcode

	This would normally print "1", but if Zott was defined with a DEFINE macro, it will print "one".
	
	You can also use the stream operators with an enum directly:

	\code
		Zott zott = Zott::ten;
		std::cout << "Zott is '" << zott << "' as of now.";
	\endcode

	This will print "Zott is 'ten' as of now."

	\code
		Zott zott;
		std::cin >> zott;
	\endcode

	This will take "zero", "one", "two" or "ten" as an input and assign the corresponding value.
	What happens when the input is invalid can be changed in the options.

	If an enum is defined with the DEFINE_FLAG macro, its output will be split into
	all binary flags set to 1:

	\code
		Action action = Action::move;
		action |= Action::fly;
		std::cout << action;
	\endcode

	This will print "move | fly" or "fly | move", depending on the defintion order of the values.

	More on flag-enums later.






	\subsection Tuples PP-Tuples (tup, dtup, atup)

	Preprocessor Tuples are a subset of the Tuples from Boost.Preprocessor and are 
	used to describe a single enumerator and its properties.

	These properties are:

	- *name*	- Name of the enumerator.
	- *value*	- Integral value of the enumerator. Is supplied by a Boost.Enum Supply if omitted.
	- *string*	- String representation of the enumerator. Is determined by stringizing *name* if omitted.

	PP-Tuples come in many different shapes, which are divided into two groups, dtups and atups.
	dtups are used in DEFINE macros and can have one of the following forms:

	- `(name)`
	- `(name, (value))`
	- `(name, _, string)`
	- `(name, (value), string)`

	As you've seen in the section Quickstart, ADAPT macros don't need *value* to be specified,
	so atups only come in two shapes:

	- `(name)`
	- `(name, string)`

	\note `(name, string)` is NOT a valid dtup! *value* HAS to be explicitly specified as empty by
	using `_` as a replacement.

	A Tuple seldom comes alone, though.






	\subsection Sequences PP-Sequences (seq, dseq, aseq)

	A Preprocessor Sequence is a concatenation of one to arbitrarly many PP-Tuples, and will look somewhat like this:

	\code
		(one)(two, (2), "two")(three)
	\endcode

	The Tuples can be divided by whitespace characters as well, so this is equal to the PP-Sequence above:

	\code
		(one)
		(two, (2), "two")
		(three)
	\endcode

	As opposed to Sequences in Boost.Preprocessor, PP-Sequences in Boost.Enum can be arbitrarily long.

	Just like Tuples, Sequences come in two flavours, dseq and aseq. The former is only made of dtups, the latter only of atups.
	Mixing the two kinds of tuples in a PP-Sequence is not allowed.

	\warning This means that if a dseq is required, you can't use the atup (*name*, *string*), but have to 
	use (*name*, _, *string*) instead!

	Which type of sequence a macro takes is denounced by the argument name:
	
	- `BOOST_ENUM_EXP_DS(dseq)` only takes a dseq
	- `BOOST_ENUM_EXP_AS(aseq)` only takes an aseq
	- `BOOST_ENUM_EXP_S(seq)` can take either

	Not supplying the correct type of PP-Sequence will lead to a compilation error in most cases.







	\subsection Options

	Boost.Enum offers the ability to greatly customise the bahviour of the enumerations you define.
	The main way of doing this is the boost::enum_::options template class in combination with _W_OPTIONS macros:

	\code
		BOOST_ENUM_DEFINE_W_OPTIONS(Zott, 
			(boost::enum_::options<>),
			(zero)
			(one)
			(two)
			(ten, (10))
		)
	\endcode

	This is equivalent to using the regular BOOST_ENUM_DEFINE macro, but we want to do something different.
	For example, we could want an enum that is allowed to have values other than its defined values, like normal
	C++ enums are. Say we also want to use a map for the string conversion lookup, change its type to 
	`unsigned char` and use our custom string type "awesome_string".
	Just change the first two lines from the example above to:

	\code
		using namespace boost::enum_; //only in .cpp files!
		
		BOOST_ENUM_DEFINE_W_OPTIONS(Zott,
			(options<option_vals::arbitrary | option_vals::map_lookup, unsigned char, supplies::NoCustomSupply, awesome_string>),
	\endcode

	A bit long, but does the job. When changing just a single argument, instead of repeating all the standard ones,
	enum_::options offers a better solution:

	\code
		(options<>::WithStringT<awesome_string>)
	\endcode

	Full details about all options can be found in the boost::enum_::options documentation.

	If you need to adapt an enum with options, use BOOST_ENUM_ADAPT_W_OPTIONS along with adapt_options:

	\code
		BOOST_ENUM_ADAPT(Zott,
			(boost::enum_::adapt_options<>)
			(zero)
			(one)
			(two)
			(ten)
		)
	\endcode

	\note `adapt_options` has to be used as not all options are available when adapting an existing enum, and while
	`adapt_options` and `options` work similarly, they are not interchangeable in the macros argument list.





	\subsection Supplies

	One of the more complex options to modify the bahviour of an enumeration is the Supply.
	It is basically a constant expression that determines the numerical value of enumerator.

	With C++ enumerations, an enuerator with an unspecified value will take on the value of the
	previous enumerator plus one.
	The corresponding supply in Boost.Enum is supplies::increment,
	even though it doesn't behave exactly the same way.

	Internally, a supply is a class that has the following form:
	\code
		struct *supplyName*{
			typedef *integral type* UnderlyingT;
			template<UnderlyingT Index>
			struct values{
				typedef UnderlyingT UnderlyingT;
				enum : UnderlyingT{ value = *Calculation of value* };
			};
		};
	\endcode

	Instead of specifying UnderlyingT strictly, you can also make the class a template.
	As an example, he `supplies::increment` supply looks like this:
	\code
		template<typename UnderlyingT>
		struct increment{
			typedef UnderlyingT UnderlyingT;
			template<UnderlyingT Index>
			struct values{
				typedef UnderlyingT UnderlyingT;
				enum : UnderlyingT{ value = Index };
		};
	};
	\endcode

	As you might notice, there is a difference between the way C++ enumerations and Boost enumerations handle value generation.
	Supplies only know the current index, not the previously generated value.
	So with supplies::increment, if you set the first value of an enum to be 7, the second one will still be 1, not 8.

*/
