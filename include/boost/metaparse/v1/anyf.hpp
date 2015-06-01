#ifndef BOOST_METAPARSE_V2_ANYF_HPP
#define BOOST_METAPARSE_V2_ANYF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldlf.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/lambda.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct anyf :
        foldlf<
          P,
          boost::mpl::vector<>,
          typename boost::mpl::lambda<
            boost::mpl::push_back<boost::mpl::_1, boost::mpl::_2>
          >::type
        >
      {};
    }
  }
}

#endif

