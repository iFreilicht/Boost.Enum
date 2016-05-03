# Boost.Enum

A C++11 header-only library that allows you to enhance the functionality of scoped enumerations (unscoped in progress)
at your discretion. It is not part of boost yet. A few features are:

- **String conversion**: Convert an enumerator not only to its underlying value but also to its actual name
- **iostream compatibility**: Use the extraction and insertion operators with istreams and ostreams
- **Binary flag enums**: Define full-featured binary flags with ease, readable string output included
- **Runtime value checks**: Allow or disallow only defined values to be assigned to a variable
- **Ordering control**: Allow or disallow ordering for your enumerators
- **Generation behaviour**: Change the conventions by which values for enumerators are chosen

##Quickstart

To use Boost.Enum, simply download this repository and add the "include" directory to your include path.
All dependencies (Boost.Config and Boost.Preprocessor) are in this repository as well. Remove them if you have Boost installed. 
Then, change the definition of an enum from this
```
enum class Zott{
		zero,
		one,
		two,
		ten = 10
};
```

to this:

```
#include <boost/enum/define.hpp>

BOOST_ENUM_DEFINE(Zott,
	(zero)
	(one)
	(two)
	(ten, (10))
)
```

This will instantly allow you to do the following.

Convert to and from std::string.
```
Zott var = static_cast<Zott>("one");
std::string str = static_cast<std::string>(var);
```

Extract and insert from and to std::ostreams and std::istreams.
```
std::cin >> var;	//can take values ("1") or names ("one")
std::out << var;	//will output names ("one")
```

Boost.Enum has only been tested on MSVC so far.
