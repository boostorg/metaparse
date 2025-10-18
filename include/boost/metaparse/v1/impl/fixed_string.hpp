#ifndef BOOST_METAPARSE_V1_IMPL_FIXED_STRING_HPP
#define BOOST_METAPARSE_V1_IMPL_FIXED_STRING_HPP

// Copyright Denis Mikhailov 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstddef> // for std::size_t

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template<typename CharT, std::size_t N>
        struct fixed_string {
            const CharT* data;
            constexpr fixed_string(const CharT (&s)[N]) noexcept
              : data{s}
            {}
            constexpr CharT operator[](std::size_t i) const noexcept { return data[i]; }
            constexpr std::size_t size() const noexcept { return N; }
        };

        template<typename CharT, std::size_t N>
        constexpr fixed_string<CharT, N> make_fixed_string(const CharT(&s)[N]) noexcept {
            return {s};
        }
      }
    }
  }
}

#endif

