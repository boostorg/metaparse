# digit_val

## Synopsis

```cpp
struct digit_val;
```

This is a [parser](parser.html).

## Description

It accepts one character in the range `0-9`. The result of the parser is the
value represented by the accepted character.

## Header

```cpp
#include <boost/metaparse/digit_val.hpp>
```

## Expression semantics

The following are equivalent:

```cpp
digit_val

transform<digit, util::digit_to_int<>>
```

## Example

```cpp
#include <boost/metaparse/digit_val.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_result.hpp>

using namespace boost::metaparse;

static_assert(
  !is_error<digit_val::apply<BOOST_STRING("0"), start>>::type::value,
  "digit_val should accept a digit"
);

static_assert(
  is_error<digit_val::apply<BOOST_STRING("x"), start>>::type::value,
  "digit_val should reject a character"
);

static_assert(
  get_result<digit_val::apply<BOOST_STRING("0"), start>>::type::value == 0,
  "the result of parsing should be the int value"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

