# space

## Synopsis

```cpp
struct space;
```

This is a [parser](parser.html).

## Description

`space` accepts one white space character. The result of parsing is the parsed
character.

## Header

```cpp
#include <boost/metaparse/space.hpp>
```

## Expression semantics

The followin are equivalent:

```cpp
space

accept_when<one_char, util::is_whitespace<>, errors::whitespace_expected>
```

## Example

```cpp
#include <boost/metaparse/space.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_remaining.hpp>

#include <type_traits>

using namespace boost::metaparse;

static_assert(
  std::is_same<
    BOOST_METAPARSE_STRING(" foo"),
    get_remaining<space::apply<BOOST_METAPARSE_STRING("  foo"), start>>::type
  >::type::value,
  "it should consume the first space of the input"
);

static_assert(
  is_error<space::apply<BOOST_METAPARSE_STRING("x"), start>>::type::value,
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

