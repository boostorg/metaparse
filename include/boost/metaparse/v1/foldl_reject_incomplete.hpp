#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_at_first_char_expected.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl_reject_incomplete
      {
      private:
        template <class Res>
        struct apply_unchecked :
          // I need to use apply_wrap, and not apply, because apply would
          // build a metafunction class from foldl<P, State, ForwardOp>
          // when ForwardOp is a lambda expression.
          boost::mpl::apply_wrap2<
            foldl_reject_incomplete<
              P,
              boost::mpl::apply<
                ForwardOp,
                typename State::type,
                typename get_result<Res>::type
              >,
              ForwardOp
            >,
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};

      template <class S, class Pos>
      struct end_of_folding :
        boost::mpl::eval_if<
          typename boost::mpl::equal_to<
            typename Pos::type,
            typename get_position< boost::mpl::apply<P, S, Pos> >::type
          >::type,
          accept<State, S, Pos>,
          boost::mpl::apply<P, S, Pos>
        >
      {};
      public:
        typedef foldl_reject_incomplete type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<boost::mpl::apply<P, S, Pos> >::type,
            end_of_folding<S, Pos>,
            apply_unchecked<boost::mpl::apply<P, S, Pos> >
          >
        {};
      };
    }
  }
}

#endif

