#ifndef BOOST_METAPARSE_V1_CPP17_STRING_VALUE_HPP
#define BOOST_METAPARSE_V1_CPP17_STRING_VALUE_HPP

// Copyright Denis Mikhailov 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/fixed_string.hpp>
#include <boost/metaparse/v1/cpp17/impl/convert_string.hpp>

#include <utility> // for std::make_index_sequence

#ifdef BOOST_METAPARSE_V1_STRING_VALUE
#error BOOST_METAPARSE_V1_STRING_VALUE already defined
#endif

#define BOOST_METAPARSE_V1_STRING_VALUE(s) ([]{                                                \
    namespace impl = ::boost::metaparse::v1::impl;                                             \
    static constexpr auto fs = impl::make_fixed_string(s);                                     \
    return impl::convert_string<fs>::apply(std::make_index_sequence<fs.size() - 1>{});         \
}())

#endif

