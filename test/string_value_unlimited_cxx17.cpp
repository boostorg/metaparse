// Copyright Denis Mikhailov 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE string_value_unlimited_cxx17

#define BOOST_METAPARSE_LIMIT_STRING_SIZE 4
#include <boost/metaparse/string.hpp>
#include <boost/metaparse/string_value.hpp>

#include <boost/test/unit_test.hpp>

#include <type_traits>

BOOST_AUTO_TEST_CASE(test_string_value_unlimited_cxx17)
{
  auto abcde = BOOST_METAPARSE_STRING_VALUE("abcde");

  BOOST_MPL_ASSERT((
    std::is_same<boost::metaparse::string<'a', 'b', 'c', 'd', 'e'>, decltype(abcde)>
  ));
}

