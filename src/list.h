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

}

#endif  // CONST_LIST_SRC_LIST_H_
