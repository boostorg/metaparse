#ifndef BOOST_METAPARSE_V1_IMPL_STRING_AT_HPP
#define BOOST_METAPARSE_V1_IMPL_STRING_AT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/metaparse/v1/impl/no_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int MaxLen, int Len, class T>
        BOOST_CONSTEXPR int string_at(const T (&s)[Len], int n)
        {
          // "MaxLen + 1" adds the \0 character of the string literal to the
          // limit
          BOOST_STATIC_ASSERT((Len <= MaxLen + 1));
          return n >= Len - 1 ? BOOST_NO_CHAR : s[n];
        }
      }
    }
  }
}

#ifdef BOOST_METAPARSE_V1_STRING_AT
#  error BOOST_METAPARSE_V1_STRING_AT already defined
#endif
#define BOOST_METAPARSE_V1_STRING_AT \
  ::boost::metaparse::v1::impl::string_at<BOOST_METAPARSE_LIMIT_STRING_SIZE>

#ifdef BOOST_METAPARSE_V1_STRING_AT1
#  error BOOST_METAPARSE_V1_STRING_AT1 already defined
#endif
#define BOOST_METAPARSE_V1_STRING_AT1(s, prefix) \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 0), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 1), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 2), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 3), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 4), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 5), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 6), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 7), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 8), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## 9), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## a), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## b), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## c), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## d), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## e), \
  BOOST_METAPARSE_V1_STRING_AT((s), 0x ## prefix ## f)


#ifdef BOOST_METAPARSE_V1_STRING_AT2
#  error BOOST_METAPARSE_V1_STRING_AT2 already defined
#endif
#define BOOST_METAPARSE_V1_STRING_AT2(s, prefix) \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 0), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 1), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 2), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 3), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 4), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 5), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 6), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 7), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 8), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## 9), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## a), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## b), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## c), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## d), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## e), \
  BOOST_METAPARSE_V1_STRING_AT1((s), prefix ## f)

#ifdef BOOST_METAPARSE_V1_STRING_AT3
#  error BOOST_METAPARSE_V1_STRING_AT3 already defined
#endif
#define BOOST_METAPARSE_V1_STRING_AT3(s, prefix) \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 0), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 1), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 2), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 3), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 4), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 5), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 6), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 7), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 8), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## 9), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## a), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## b), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## c), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## d), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## e), \
  BOOST_METAPARSE_V1_STRING_AT2((s), prefix ## f)

#endif

