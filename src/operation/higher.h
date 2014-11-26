#ifndef CONST_LIST_SRC_OPERATION_HIGHER_H_
#define CONST_LIST_SRC_OPERATION_HIGHER_H_

#include <cons.h>
#include <make.h>
#include <detail/type/sfinae.h>

#include "specialized.h"
#include "concatenate.h"

namespace ConstList {

template <
	typename Cons,
	typename Function,
	typename Intitial,
	detail::enable_if<is_empty_cons<Cons>::value> = 0
>
constexpr auto foldr(const Cons&, const Function&, const Intitial& initial) {
	return initial;
}

template <
	typename Cons,
	typename Function,
	typename Intitial,
	detail::enable_if<!is_empty_cons<Cons>::value> = 0
>
constexpr auto foldr(
	const Cons&     cons,
	const Function& function,
	const Intitial& initial
) {
	return function(
		cons.car,
		foldr(cons.cdr, function, initial)
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
		ConstList::make()
	);
}

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

#endif  // CONST_LIST_SRC_OPERATION_HIGHER_H_
