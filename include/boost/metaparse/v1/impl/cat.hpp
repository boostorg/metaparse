// no include guard: the header might be included multiple times

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_METAPARSE_V1_CAT_IMPL
#  error BOOST_METAPARSE_V1_CAT_IMPL already defined
#endif
#define BOOST_METAPARSE_V1_CAT_IMPL(a, b) a ## b

#ifdef BOOST_METAPARSE_V1_CAT
#  error BOOST_METAPARSE_V1_CAT already defined
#endif
#define BOOST_METAPARSE_V1_CAT(a, b) BOOST_METAPARSE_V1_CAT_IMPL(a, b)

