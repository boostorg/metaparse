#ifndef BOOST_METAPARSE_V1_CPP17_IMPL_CONVERT_STRING_HPP
#define BOOST_METAPARSE_V1_CPP17_IMPL_CONVERT_STRING_HPP

// Copyright Denis Mikhailov 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/string.hpp>

#include <cstddef> // for std::size_t
#include <utility> // for std::make_index_sequence

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template<const auto& S>
        struct convert_string {
          template<std::size_t... Is>
          static constexpr auto apply(std::index_sequence<Is...>) noexcept {
            return ::boost::metaparse::v1::string<S[Is]...>{};
          }
        };
      }
    }
  }
}

#endif

