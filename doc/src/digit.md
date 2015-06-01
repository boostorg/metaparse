# digit

## Synopsis

```cpp
struct digit;
```

This is a [parser](parser.html).

## Description

Parser accepting one character in the range `0-9`. The
result of the parser is the accepted character.

## Header

```cpp
#include <boost/metaparse/digit.hpp>
```

## Expression semantics

The following are equivalent:

```cpp
digit

accept_when<one_char, util::is_digit, error::digit_expected>
```

## Example

```cpp
#include <boost/metaparse/digit.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_result.hpp>

using namespace boost::metaparse;

static_assert(
  !is_error<digit::apply<BOOST_STRING("0"), start>>::type::value,
  "digit should accept a digit"
);

static_assert(
  is_error<digit::apply<BOOST_STRING("x"), start>>::type::value,
  "digit should reject a character"
);

static_assert(
  get_result<digit::apply<BOOST_STRING("0"), start>>::type::value == '0',
  "the result of parsing should be the character value"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)


