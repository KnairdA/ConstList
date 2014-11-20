#ifndef CONST_LIST_SRC_CONS_H_
#define CONST_LIST_SRC_CONS_H_

#include "detail/cons.h"

namespace ConstList {

using detail::is_cons;
using detail::is_empty_cons;

/*------------------------------------------------------------------------------
 `Cons` is used to represent the actual list structures of this library.
 i.e. it fullfills the purpose of LISP's `cons` function in a fashion which is
 compatible to the C++ templating system.

 `CAR`: non-void type depicting the value of the `Cons` element
 `CDR`: `void` or `Cons` specialization depicting the next element of the list

 The actual implementation of `Cons` is contained within either `ConsWithCdr`,
 `ConsWithoutCdr` or `ConsEmpty` as decided by `detail::select_cons`

 Note: `void` is internally mapped to `ConsEmpty` by `detail::select_cons`
------------------------------------------------------------------------------*/

template <
	typename CAR,
	typename CDR
>
struct Cons : detail::select_cons<CAR, CDR>::type {
	typedef typename detail::select_cons<CAR, CDR>::type base;

	using base::base;
};

/*------------------------------------------------------------------------------
 Recursively resolves a given `Cons` specialization back into a flat variadic
 parameter list contained within `detail::ConsTypeList`.

 This is required for easy determination of the `Cons` structure size.
------------------------------------------------------------------------------*/

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
