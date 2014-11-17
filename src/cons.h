#ifndef CONST_LIST_SRC_CONS_H_
#define CONST_LIST_SRC_CONS_H_

#include "detail/cons.h"

namespace ConstList {

using detail::is_cons;
using detail::is_empty_cons;

template <
	typename CAR,
	typename CDR
>
struct Cons : detail::select_cons<CAR, CDR>::type {
	typedef typename detail::select_cons<CAR, CDR>::type base;

	using base::base;
};

template <
	typename    Cons,
	typename... Current
>
struct flatten_cons {
	static_assert(
		is_cons<Cons>::value,
		"Cons must be a instantiation of Cons"
	);

	typedef typename std::conditional<
		is_empty_cons<typename Cons::cdr_type>::value,
		detail::ConsTypeList<                 Current..., typename Cons::car_type>,
		flatten_cons<typename Cons::cdr_type, Current..., typename Cons::car_type>
	>::type::type type;
};

}

#endif  // CONST_LIST_SRC_CONS_H_
