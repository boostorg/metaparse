#ifndef BOOST_METAPARSE_DEFINE_ERROR_HPP
#define BOOST_METAPARSE_DEFINE_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/define_error.hpp>

#ifdef BOOST_DEFINE_ERROR
#  error BOOST_DEFINE_ERROR already defined
#endif
#define BOOST_DEFINE_ERROR BOOST_V2_DEFINE_ERROR

#endif

