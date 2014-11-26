#ifndef CONST_LIST_SRC_OPERATION_HIGHER_MISC_H_
#define CONST_LIST_SRC_OPERATION_HIGHER_MISC_H_

#include <cons.h>
#include <make.h>
#include <operation/concatenate.h>

#include "foldr.h"

namespace ConstList {

template <
	typename Cons,
	typename Function
>
constexpr auto map(const Cons& cons, const Function& function) {
	return foldr(
		cons,
		[&function](auto car, auto cdr) {
			return concatenate(make(function(car)), cdr);
		},
		make()
	);
}

template <typename Cons>
constexpr auto reverse(const Cons& cons) {
	return foldr(
		cons,
		[](auto car, auto cdr) {
			return concatenate(cdr, make(car));
		},
		make()
	);
}

template <
	typename Cons,
	typename Function,
	typename Intitial
>
constexpr auto foldl(
	const Cons&     cons,
	const Function& function,
	const Intitial& initial
) {
	return foldr(
		reverse(cons),
		[&function](auto car, auto cdr) {
			return function(cdr, car);
		},
		initial
	);
}

}


#endif  // CONST_LIST_SRC_OPERATION_HIGHER_MISC_H_
