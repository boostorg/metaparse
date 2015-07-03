# get_position

## Synopsis

```cpp
template <class D>
struct get_position;
```

This is a [lazy template metafunction](lazy_metafunction.html).

## Arguments

<table cellpadding='0' cellspacing='0'>
  <tr>
    <td>`D`</td>
    <td>[accept](accept.html) or [reject](reject.html) value</td>
  </tr>
</table>

## Description

Returns the source position information of a parsing result.

## Header

```cpp
#include <boost/metaparse/get_position.hpp>
```

## Example

```cpp
#include <boost/metaparse/get_position.hpp>
#include <boost/metaparse/start.hpp>
#include <boost/metaparse/accept.hpp>
#include <boost/metaparse/reject.hpp>
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/define_error.hpp>

#include <type_traits>

using namespace boost::metaparse;

BOOST_METAPARSE_DEFINE_ERROR(sample_error, "Sample error message");

struct returns_reject
{
  using type = reject<sample_error, start>;
};

static_assert(
  std::is_same<
    start,
    get_position<reject<sample_error, start>>::type
  >::type::value,
  "It should return the position of a reject"
);

static_assert(
  std::is_same<
    start,
    get_position<
      accept<sample_error, BOOST_METAPARSE_STRING("foo"), start>
    >::type
  >::type::value,
  "It should return the position of an accept"
);

static_assert(
  std::is_same<start, get_position<returns_reject>::type>::type::value,
  "It should support lazy evaluation"
);
```

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](reference.html)

