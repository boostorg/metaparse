// Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/foldr_reject_incomplete.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/lambda.hpp>

using boost::metaparse::foldr_reject_incomplete;

using boost::mpl::list;
using boost::mpl::push_front;
using boost::mpl::_1;
using boost::mpl::_2;
using boost::mpl::lambda;

namespace
{
  template <class P>
  struct repeated_reject_incomplete :
    foldr_reject_incomplete<P, list<>, lambda<push_front<_1, _2> >::type>
  {};
}

#define TEST_NAME foldr_reject_incomplete

#include "repeated_reject_incomplete_test.hpp"

