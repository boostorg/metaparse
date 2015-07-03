# nth_of

## Synopsis

```cpp
template <class N, class P0, /* ... */, class Pk>
struct nth_of;
```

This is a [parser combinator](parser_combinator.html).

## Arguments

<table cellpadding='0' cellspacing='0'>
  <tr>
    <td>`N`</td>
    <td>[boxed](boxed_value.html) integer value in the range `[0..k]`</td>
  </tr>
  <tr>
    <td>`P0`..`Pk`</td>
    <td>[parser](parser.html)s</td>
  </tr>
</table>

## Description

`nth_of` applies the `P0` .. `Pk` parsers in sequence. It accepts an input when
all of these parsers accept it. The result of parsing is the result of the `N`.
parser.

The maximum number of parsers `nth_of` accepts can be specified with the
`BOOST_LIMIT_SEQUENCE_SIZE` macro. Its default value is `5`.

## Header

```cpp
#include <boost/metaparse/nth_of.hpp>
```

## Expression semantics

For any `p0`, ..., `pn` parsers and `k` boxed integer value the following are
equivalent

```cpp
nth_of<k, p0, ..., pn>

nth_of_c<k::type::value, p0, ..., pn>
```

## Example

```cpp
#include <boost/metaparse/nth_of.hpp>
#include <boost/metaparse/int_.hpp>
#include <boost/metaparse/lit_c.hpp>
#include <boost/metaparse/token.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_result.hpp>

#include <type_traits>

using namespace boost::metaparse;

using int_token = token<int_>;
using left_paren_token = token<lit_c<'('>>;
using right_paren_token = token<lit_c<')'>>;

using int_in_parens =
  nth_of<
    std::integral_constant<int, 1>,
    left_paren_token, int_token, right_paren_token
  >;

static_assert(
  get_result<
    int_in_parens::apply<BOOST_METAPARSE_STRING("(13)"), start>
  >::type::value == 13,
  "it should return the result of the second parser"
);

static_assert(
  is_error<
    int_in_parens::apply<BOOST_METAPARSE_STRING("13"), start>
  >::type::value,
  "it should reject the input when there are no parens"
);

static_assert(
  is_error<
    int_in_parens::apply<BOOST_METAPARSE_STRING("(13"), start>
  >::type::value,
  "it should reject the input when there is no closing paren"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

