# spaces

## Synopsis

```cpp
struct spaces;
```

This is a [parser](parser.html).

## Description

`spaces` accepts any number of whitespace characters. It requires at least one
to be present.

## Header

```cpp
#include <boost/metaparse/spaces.hpp>
```

## Expression semantics

```cpp
spaces
```

is equivalent to

```cpp
any1<space>
```

## Example

```cpp
#include <boost/metaparse/spaces.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_remaining.hpp>

#include <type_traits>

using namespace boost::metaparse;

static_assert(
  std::is_same<
    BOOST_STRING("foo"),
    get_remaining<spaces::apply<BOOST_STRING("  foo"), start>>::type
  >::type::value,
  "it should consume all whitespaces at the beginning of the input"
);

static_assert(
  is_error<spaces::apply<BOOST_STRING("x"), start>>::type::value,
  "it should return an error when the input does not begin with a whitespace"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

