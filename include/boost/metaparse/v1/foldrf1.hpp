#ifndef BOOST_METAPARSE_V1_FOLDRF1_HPP
#define BOOST_METAPARSE_V1_FOLDRF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldrf.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldrf1
      {
        typedef foldrf1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<boost::mpl::apply<P, S, Pos> >,
            P,
            foldrf<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif

