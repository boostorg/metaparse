#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/apply_wrap.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_reject_incomplete_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          boost::mpl::apply_wrap2<
            foldl_reject_incomplete<
              P,
              typename get_result<Res>::type,
              ForwardOp
            >,
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_reject_incomplete_start_with_parser type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<boost::mpl::apply<StateP, S, Pos> >::type,
            boost::mpl::apply<StateP, S, Pos>,
            apply_unchecked<boost::mpl::apply<StateP, S, Pos> >
          >
        {};
      };
    }
  }
}

#endif

