# boost::metaparse versioning

This section describes how the library is prepared for supporting multiple
(not backward compatible) changes.

## Template classes

The elements of the library are defined in the `boost::metaparse::v1`
namespace. For example the `one_char` class is
`boost::metaparse::v1::one_char` and is available after including the
`<boost/metaparse/v1/one_char.hpp>` header file.

At the same time the library provides the `<boost/metaparse/one_char.hpp>`
header file which includes `<boost/metaparse/v1/one_char.hpp>` and contains
the following:

```cpp
namespace boost
{
  namespace metaparse
  {
    using v1::one_char;
  }
}
```

This makes it possible to use `one_char` as `boost::metaparse::one_char`.

Future versions of the library may provide other namespaces (eg. `v3`). The
header files in `<boost/metaparse/...>` provide the latest version of the
library. To always get version `v1`, one should use header files in
`<boost/metaparse/v1/...>`.

The library does not use inline namespaces to work on compilers that do not
support them.

## Macros

Macros defined by the library are prefixed with `BOOST_METAPARSE_V1_`. For
example `BOOST_METAPARSE_V1_STRING`. It is defined in the
`<boost/metaparse/v1/string.hpp>` header file. The library provides the
`<boost/metaparse/srting.hpp>` header file as well, which includes the
definition of this macro and provides the following definition:

```cpp
#define BOOST_METAPARSE_STRING BOOST_METAPARSE_V1_STRING
```

This makes it possible to use the macro as `BOOST_METAPARSE_STRING`. Future
versions of the library may define other versions of this macro (eg.
`BOOST_V2_STRING`). `BOOST_METAPARSE_STRING` will refer to the latest version.

This versioning does not affect macros that may be overridden by the code using
the library. (eg. `BOOST_LIMIT_STRING_SIZE`)

## Migration from `v1`

The callback functions of [`foldl`](foldl.html), [`foldl1`](foldl1.html),
[`foldlp`](foldlp.html), [`foldr`](foldr.html), [`foldr1`](foldr1.html),
[`foldrp`](foldrp.html) expect their arguments in reverse order in `v1` compared
to `v1`. To help migration, Metaparse provides the [`v1::swap`](swap.html)
metafunction class.

<p class="copyright">
Copyright Abel Sinkovics (abel at elte dot hu) 2011.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
[http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt)
</p>

[[up]](index.html)
<br />
