#ifndef BOOST_METAPARSE_V1_LIT_C_HPP
#define BOOST_METAPARSE_V1_LIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/char.hpp>

#include <boost/metaparse/v1/error/literal_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C>
      struct lit_c :
        accept_when<
          change_error_message<one_char, error::literal_expected<C> >,
          typename boost::mpl::lambda<
            boost::mpl::equal_to<boost::mpl::_1, boost::mpl::char_<C> >
          >::type,
          error::literal_expected<C>
        >
      {};
    }
  }
}

#endif

