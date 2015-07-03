# alphanum

## Synopsis

```cpp
struct alphanum;
```

This is a [parser](parser.html).

## Description

It accepts one character in the range `a-z`, `A-Z` or `0-9`. The
result of the parser is the accepted character.

## Header

```cpp
#include <boost/metaparse/alphanum.hpp>
```

## Expression semantics

The following are equivalent:

```cpp
alphanum

one_of<digit, letter>
```

## Example

```cpp
#include <boost/metaparse/alphanum.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_result.hpp>

using namespace boost::metaparse;

static_assert(
  !is_error<alphanum::apply<BOOST_METAPARSE_STRING("0"), start>>::type::value,
  "alphanum should accept a digit"
);

static_assert(
  !is_error<alphanum::apply<BOOST_METAPARSE_STRING("x"), start>>::type::value,
  "alphanum should accept a character"
);

static_assert(
  get_result<
    alphanum::apply<BOOST_METAPARSE_STRING("x"), start>
  >::type::value == 'x',
  "the result of parsing should be the character value"
);

static_assert(
  is_error<alphanum::apply<BOOST_METAPARSE_STRING(","), start>>::type::value,
  "alphanum should reject a comma"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

