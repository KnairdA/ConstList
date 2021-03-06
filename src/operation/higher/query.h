#ifndef CONST_LIST_SRC_OPERATION_HIGHER_QUERY_H_
#define CONST_LIST_SRC_OPERATION_HIGHER_QUERY_H_

#include <cons.h>
#include <make.h>

#include "foldr.h"

namespace ConstList {

template <
	typename Cons,
	typename Function,
	detail::enable_if<is_empty_cons<Cons>::value> = 0
>
constexpr bool any(const Cons&, const Function&) {
	return false;
}

template <
	typename Cons,
	typename Function,
	detail::enable_if<!is_empty_cons<Cons>::value> = 0
>
constexpr bool any(const Cons& cons, const Function& function) {
	static_assert(
		std::is_same<decltype(function(cons.car)), bool>::value,
		"Functor must return boolean for `any` to work"
	);

	if ( function(cons.car) ) {
		return true;
	} else {
		return false || any(cons.cdr, function);
	}
}

template <
	typename Cons,
	typename Function
>
constexpr bool all(const Cons& cons, const Function& function) {
	return foldr(
		cons,
		[&function](auto car, auto cdr) -> bool {
			return function(car) && cdr;
		},
		true
	);
}

template <
	typename Cons,
	typename Function
>
constexpr bool none(const Cons& cons, const Function& function) {
	return !any(
		cons,
		[&function](auto car) -> bool {
			return function(car);
		}
	);
}

template <
	typename Cons,
	typename Function
>
constexpr std::size_t count(const Cons& cons, const Function& function) {
	return foldr(
		cons,
		[&function](auto car, const std::size_t& cdr) -> std::size_t {
			static_assert(
				std::is_same<decltype(function(car)), bool>::value,
				"Functor must return boolean for `count` to work"
			);

			if ( function(car) ) {
				return cdr + 1;
			} else {
				return cdr;
			}
		},
		std::size_t{0}
	);
}

}

#endif  // CONST_LIST_SRC_OPERATION_HIGHER_QUERY_H_
