// no include guard: the header might be included multiple times

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_METAPARSE_V1_SPECIALISE_STRING
#  error BOOST_METAPARSE_V1_SPECIALISE_STRING already defined
#endif
#define BOOST_METAPARSE_V1_SPECIALISE_STRING(spec_length, no_char_count) \
  template <BOOST_METAPARSE_V1_ENUM_PARAMS(spec_length, char C)> \
  struct BOOST_METAPARSE_V1_CAT(string, BOOST_METAPARSE_V1_TMP_LENGTH_LIMIT)< \
    BOOST_METAPARSE_V1_ENUM_PARAMS(spec_length, C), \
    BOOST_METAPARSE_V1_ENUM_CONSTANT(no_char_count, BOOST_NO_CHAR) \
  > : \
    boost::metaparse::v1::string< \
      BOOST_METAPARSE_V1_ENUM_PARAMS(spec_length, C) \
    > \
  {};
    

#ifdef BOOST_METAPARSE_V1_SPECIALISE_STRING0
#  error BOOST_METAPARSE_V1_SPECIALISE_STRING0 already defined
#endif
#define BOOST_METAPARSE_V1_SPECIALISE_STRING0 \
  template <> \
  struct BOOST_METAPARSE_V1_CAT(string, BOOST_METAPARSE_V1_TMP_LENGTH_LIMIT)< \
    BOOST_METAPARSE_V1_ENUM_CONSTANT( \
      BOOST_METAPARSE_V1_TMP_LENGTH_LIMIT, \
      BOOST_NO_CHAR \
    ) \
  > : \
    boost::metaparse::v1::string<> \
  {};
    
#ifdef BOOST_METAPARSE_V1_
#  error BOOST_METAPARSE_V1_ already defined
#endif
#define BOOST_METAPARSE_V1_ BOOST_METAPARSE_V1_SPECIALISE_STRING

