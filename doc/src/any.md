# any

## Synopsis

```cpp
template <class P>
struct any;
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

It applies `P` on the input string repeatedly as long as `P` accepts the input.
The result of parsing is a sequence of the results of the individual
applications of `P`.

When `P` rejects the input for the first time, `any` still accepts the
input and the result of parsing is an empty sequence.

Here is a diagram showing how `any` works by example:

```cpp
using int_token = token<int_>;
```

<p align="center">
  <a href="any_diag1.png"><img src="any_diag1.png" style="width:70%" /></a>
</p>

Further details can be found in the [Repetition](manual.html#repetition) section
of the [User Manual](manual.html).

## Header

```cpp
#include <boost/metaparse/any.hpp>
```

## Expression semantics

For any `p` parser the following are equivalent:

```cpp
any<p>

foldl<
  p,
  /* unspecified empty sequence */,
  boost::mpl::push_back<_2, _1>
>
```

## Example

```cpp
#include <boost/metaparse/any.hpp>
#include <boost/metaparse/digit_val.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/get_result.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>

using namespace boost::metaparse;

using digits = any<digit_val>;

static_assert(
  boost::mpl::equal<
    get_result<digits::apply<BOOST_STRING("1234"), start>>::type,
    boost::mpl::vector<
      boost::mpl::int_<1>,
      boost::mpl::int_<2>,
      boost::mpl::int_<3>,
      boost::mpl::int_<4>
    >
  >::type::value,
  "the result of parsing should be the list of digit values"
);

static_assert(
  boost::mpl::equal<
    get_result<digits::apply<BOOST_STRING("x"), start>>::type,
    boost::mpl::vector<>
  >::type::value,
  "any should accept the input when it can't parse anything with digit_val"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

