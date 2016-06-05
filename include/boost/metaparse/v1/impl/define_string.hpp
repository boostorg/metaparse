// no include guard: the header might be included multiple times

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_METAPARSE_V1_DEFINE_STRING
#  error BOOST_METAPARSE_V1_DEFINE_STRING already defined
#endif
#define BOOST_METAPARSE_V1_DEFINE_STRING \
  template < \
    BOOST_METAPARSE_V1_ENUM_PARAMS( \
      BOOST_METAPARSE_V1_TMP_LENGTH_LIMIT, \
      char C \
    ) \
  > \
  struct BOOST_METAPARSE_V1_CAT(string, BOOST_METAPARSE_V1_TMP_LENGTH_LIMIT) : \
    boost::metaparse::v1::string< \
      BOOST_METAPARSE_V1_ENUM_PARAMS(BOOST_METAPARSE_V1_TMP_LENGTH_LIMIT, C) \
    > \
  {};

