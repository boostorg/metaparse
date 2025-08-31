#ifndef BOOST_METAPARSE_V1_STRING_VALUE_HPP
#define BOOST_METAPARSE_V1_STRING_VALUE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2021.
// Copyright Denis Mikhailov 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/config.hpp>

#if BOOST_METAPARSE_STD >= 2017
#  include <boost/metaparse/v1/cpp17/string_value.hpp>
#else

#  include <boost/metaparse/v1/string.hpp>

#  ifdef BOOST_METAPARSE_V1_STRING_VALUE
#  error BOOST_METAPARSE_V1_STRING_VALUE already defined
#  endif

#  ifdef BOOST_METAPARSE_V1_STRING
#  define BOOST_METAPARSE_V1_STRING_VALUE(s) (BOOST_METAPARSE_V1_STRING(s){})
#  endif

#endif

#endif

