#ifndef CONST_LIST_SRC_LIST_H_
#define CONST_LIST_SRC_LIST_H_

#include <type_traits>
#include <utility>

#include "detail/type/sfinae.h"

#include "cons.h"
#include "make.h"

namespace ConstList {

template <typename Cons>
constexpr auto head(const Cons& cons) {
	static_assert(
		detail::is_cons<Cons>::value,
		"Cons must be a instantiation of Cons"
	);

	return cons.car;
}

template <typename Cons>
constexpr auto tail(const Cons& cons) {
	static_assert(
		detail::is_cons<Cons>::value,
		"Cons must be a instantiation of Cons"
	);

	static_assert(
		detail::is_cons<typename Cons::cdr_type>::value,
		"CDR must be a instantiation of Cons if queried by tail"
	);

	return cons.cdr;
}

template <
	std::size_t Index,
	typename    Cons,
	detail::enable_if<Index == 0> = 0
>
constexpr auto nth(const Cons& cons) {
	return head(cons);
}

template <
	std::size_t Index,
	typename    Cons,
	detail::enable_if<Index != 0> = 0
>
constexpr auto nth(const Cons& cons) {
	return nth<Index - 1>(
		tail(cons)
	);
}

template <typename Cons>
constexpr std::size_t size(const Cons&) {
	return flatten_cons<Cons>::type::size;
}

template <
	std::size_t Count,
	typename    Cons,
	typename... Current,
	detail::enable_if<Count == 1> = 0
>
constexpr auto take(const Cons& cons, Current&&... cars) {
	return make(cars..., head(cons));
}

template <
	std::size_t Count,
	typename    Cons,
	typename... Current,
	detail::enable_if<Count != 1> = 0
>
constexpr auto take(const Cons& cons, Current&&... cars) {
	return take<Count - 1>(
		tail(cons),
		cars...,
		head(cons)
	);
}

template <
	typename CAR,
	typename CDR,
	detail::enable_if<
		 is_empty_cons<CAR>::value &&
		!is_empty_cons<CDR>::value
	> = 0
>
constexpr auto concatenate(const CAR&, const CDR& cdr) {
	return cdr;
}

template <
	typename CAR,
	typename CDR,
	detail::enable_if<
		!is_empty_cons<CAR>::value &&
		 is_empty_cons<CDR>::value
	> = 0
>
constexpr auto concatenate(const CAR& car, const CDR&) {
	return car;
}

template <
	typename CAR,
	typename CDR,
	detail::enable_if<
		 is_empty_cons<typename CAR::cdr_type>::value &&
		!is_empty_cons<CDR>::value
	> = 0
>
constexpr auto concatenate(const CAR& car, const CDR& cdr) {
	return make(car.car, cdr);
}

template <
	typename CAR,
	typename CDR,
	detail::enable_if<!is_empty_cons<typename CAR::cdr_type>::value> = 0
>
constexpr auto concatenate(const CAR& car, const CDR& cdr) {
	return make(
		car.car,
		concatenate(car.cdr, cdr)
	);
}

template <
	typename CAR,
	typename CDR
>
constexpr auto operator+(const CAR& car, const CDR& cdr) {
	return concatenate(car, cdr);
}

template <
	typename Cons,
	typename Function,
	typename Intitial,
	detail::enable_if<is_empty_cons<typename Cons::cdr_type>::value> = 0
>
constexpr auto foldr(
	const Cons&     cons,
	const Function& function,
	const Intitial& initial
) {
	return function(cons.car, initial);
}

template <
	typename Cons,
	typename Function,
	typename Intitial,
	detail::enable_if<!is_empty_cons<typename Cons::cdr_type>::value> = 0
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
	typename Function
>
constexpr auto map(
	const Cons&     cons,
	const Function& function
) {
	return foldr(
		cons,
		[&function](auto car, auto cdr) {
			return concatenate(make(function(car)), cdr);
		},
		ConstList::make()
	);
}

template <typename Cons>
constexpr auto reverse(const Cons& cons) {
	return foldr(
		cons,
		[](auto car, auto cdr) {
			return concatenate(cdr, ConstList::make(car));
		},
		ConstList::make()
	);
}

}

#endif  // CONST_LIST_SRC_LIST_H_
