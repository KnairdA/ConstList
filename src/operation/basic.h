#ifndef CONST_LIST_SRC_OPERATION_BASIC_H_
#define CONST_LIST_SRC_OPERATION_BASIC_H_

#include <cons.h>
#include <make.h>
#include <detail/type/sfinae.h>

namespace ConstList {

template <typename Cons>
constexpr auto head(const Cons& cons) {
	static_assert(
		is_cons<Cons>::value,
		"Cons must be a instantiation of Cons"
	);

	return cons.car;
}

template <typename Cons>
constexpr auto tail(const Cons& cons) {
	static_assert(
		is_cons<Cons>::value && !is_empty_cons<Cons>::value,
		"Cons must be a non-empty instantiation of Cons"
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
	detail::enable_if<(Count == 0 || is_empty_cons<Cons>::value)> = 0
>
constexpr auto take(const Cons&, Current&&... cars) {
	return make(cars...);
}

template <
	std::size_t Count,
	typename    Cons,
	typename... Current,
	detail::enable_if<(Count > 0 && !is_empty_cons<Cons>::value)> = 0
>
constexpr auto take(const Cons& cons, Current&&... cars) {
	return take<Count - 1>(
		tail(cons),
		cars...,
		head(cons)
	);
}

}

#endif  // CONST_LIST_SRC_OPERATION_BASIC_H_
