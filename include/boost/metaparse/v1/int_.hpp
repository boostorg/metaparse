#ifndef BOOST_METAPARSE_V1_INT__HPP
#define BOOST_METAPARSE_V1_INT__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit_val.hpp>
#include <boost/metaparse/v1/foldl1.hpp>

#include <boost/mpl/lambda.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/plus.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        foldl1<
          digit_val,
          boost::mpl::int_<0>,
          // I need to wrap it with lambda, because int_ may be used
          // in an apply and turned into a lambda expression too early.
          boost::mpl::lambda<
            boost::mpl::plus<
              boost::mpl::times<boost::mpl::_1, boost::mpl::int_<10> >,
              boost::mpl::_2
            >
          >::type
        >
        int_;
    }
  }
}

#endif

