#ifndef CONST_LIST_SRC_CONS_H_
#define CONST_LIST_SRC_CONS_H_

#include "detail/cons.h"

namespace ConstList {

using detail::is_cons;

template <
	typename CAR,
	typename CDR
>
struct Cons : detail::select_cons<CAR, CDR>::type {
	typedef typename detail::select_cons<CAR, CDR>::type base;

	using base::base;
};

}

#endif  // CONST_LIST_SRC_CONS_H_
