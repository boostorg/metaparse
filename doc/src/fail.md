# fail

## Synopsis

```cpp
template <class Msg>
struct fail;
```

This is a [parser](parser.html).

## Arguments

<table cellpadding='0' cellspacing='0'>
  <tr>
    <td>`Msg`</td>
    <td>[parsing error message](parsing_error_message.html)</td>
  </tr>
</table>

## Description

Parser rejecting every input.

## Header

```cpp
#include <boost/metaparse/fail.hpp>
```

## Expression semantics

For any `msg` parsing error message, `s` compile-time string and `pos` source
position

```cpp
fail<msg>::apply<s, pos>::type
```

returns an error with `msg` as the error message.

## Example

```cpp
#include <boost/metaparse/fail.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/is_error.hpp>
#include <boost/metaparse/get_message.hpp>
#include <boost/metaparse/define_error.hpp>

using namespace boost::metaparse;

BOOST_METAPARSE_DEFINE_ERROR(sample_error, "This is an example parsing error");

using fail_p = fail<sample_error>;

static_assert(
  is_error<fail_p::apply<BOOST_STRING("foo"), start>>::type::value,
  "it should reject every input"
);

static_assert(
  std::is_same<
    get_message<fail_p::apply<BOOST_STRING("foo"), start>>::type,
    sample_error
  >::type::value,
  "the error message should be the type specified"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

