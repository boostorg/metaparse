# fail_at_first_char_expected

## Synopsis

```cpp
template <class P>
struct fail_at_first_char_expected;
```

This is a [parser combinator](parser_combinator.html).

## Arguments

<table cellpadding='0' cellspacing='0'>
  <tr>
    <td>`P`</td>
    <td>[parser](parser.html)</td>
  </tr>
</table>

## Description

It tries to parse the input using `P`. When `P` rejects the input without
consuming any character, `fail_at_first_char_expected` accepts the input.
Otherwise (when `P` accepts the input or when it consumes characters before
rejecting the input) `fail_at_first_char_expected` rejects the input.

## Header

```cpp
#include <boost/metaparse/fail_at_first_char_expected.hpp>
```

## Expression semantics

For any `p` parser, `s` compile-time string and `pos` source position:

When `is_error<p::apply<s, pos>>::type` is false, the following are equivalent:

```cpp
fail_at_first_char_expected<p>::apply<s, pos>::type
reject<error::expected_to_fail, pos>
```

When `is_error<p::apply<s, pos>>::type` is true and
`boost::mpl::equal_to<pos, get_position<p::apply<s, pos>>::type>::type` is also
true, the following are equivalent:

```cpp
get_remaining<except<p, c, msg>, s, pos>::type
accept</* unspecified */, s, pos>
```

Otherwise the following are equivalent:

```cpp
get_remaining<except<p, c, msg>, s, pos>::type
p::apply<s, pos>::type
```

## Example

```cpp
#include <boost/metaparse/fail_at_first_char_expected.hpp>
#include <boost/metaparse/int_.hpp>
#include <boost/metaparse/lit_c.hpp>
#include <boost/metaparse/foldlp.hpp>
#include <boost/metaparse/first_of.hpp>
#include <boost/metaparse/last_of.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_result.hpp>

#include <boost/mpl/lambda.hpp>
#include <boost/mpl/plus.hpp>

using namespace boost::metaparse;

using plus_int = last_of<lit_c<'+'>, int_>;

using plus_exp =
  first_of<
    foldlp<
      plus_int,
      int_,
      boost::mpl::lambda<boost::mpl::plus<boost::mpl::_1, boost::mpl::_2>>::type
    >,
    fail_at_first_char_expected<plus_int>
  >;

static_assert(
  get_result<plus_exp::apply<BOOST_STRING("1+2+3"), start>>::type::value == 6,
  "it should accept the input when it is a list of '+' separated ints"
);

static_assert(
  is_error<plus_exp::apply<BOOST_STRING("1+2+3+"), start>>::type::value,
  "it should reject the input when it has an extra +"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2015.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

