# letter

## Synopsis

```cpp
struct letter;
```

This is a [parser](parser.html).

## Description

Parser accepting one character in the range `a-z` or `A-Z`. The result of the
parser is the accepted character.

## Header

```cpp
#include <boost/metaparse/letter.hpp>
```

## Expression semantics

The following are equivalent:

```cpp
letter

accept_when<one_char, util::is_letter<>, error::letter_expected>
```

## Example

```cpp
#include <boost/metaparse/letter.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_result.hpp>

using namespace boost::metaparse;

static_assert(
  !is_error<letter::apply<BOOST_METAPARSE_STRING("a"), start>>::type::value,
  "letter should accept a letter"
);

static_assert(
  is_error<letter::apply<BOOST_METAPARSE_STRING("0"), start>>::type::value,
  "letter should reject a digit"
);

static_assert(
  get_result<
    letter::apply<BOOST_METAPARSE_STRING("z"), start>
  >::type::value == 'z',
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

