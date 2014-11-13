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
	typename    CAR,
	typename    CDR,
	typename... CarTypes,
	typename... CdrTypes,
	typename... MergedTypes,
	detail::enable_if<(
		sizeof...(MergedTypes) == sizeof...(CarTypes)
		                        + sizeof...(CdrTypes)
	)> = 0
>
constexpr auto concatenate(
	const CAR&,
	const CDR&,
	detail::VariadicTypeList<CarTypes...>,
	detail::VariadicTypeList<CdrTypes...>,
	MergedTypes...                         values
) {
	return make(values...);
}

template <
	typename    CAR,
	typename    CDR,
	typename... CarTypes,
	typename... CdrTypes,
	typename... MergedTypes,
	detail::enable_if<(
		sizeof...(MergedTypes) < sizeof...(CarTypes)
	)> = 0
>
constexpr auto concatenate(
	const CAR&                             car,
	const CDR&                             cdr,
	detail::VariadicTypeList<CarTypes...>  carTypeList,
	detail::VariadicTypeList<CdrTypes...>  cdrTypeList,
	MergedTypes...                         values
) {
	return concatenate(
		car,
		cdr,
		carTypeList,
		cdrTypeList,
		values...,
		nth<sizeof...(MergedTypes)>(car)
	);
}

template <
	typename    CAR,
	typename    CDR,
	typename... CarTypes,
	typename... CdrTypes,
	typename... MergedTypes,
	detail::enable_if<(
		sizeof...(MergedTypes) >= sizeof...(CarTypes) &&
		sizeof...(MergedTypes) <  sizeof...(CarTypes)
		                       +  sizeof...(CdrTypes)
	)> = 0
>
constexpr auto concatenate(
	const CAR&                             car,
	const CDR&                             cdr,
	detail::VariadicTypeList<CarTypes...>  carTypeList,
	detail::VariadicTypeList<CdrTypes...>  cdrTypeList,
	MergedTypes...                         values
) {
	return concatenate(
		car,
		cdr,
		carTypeList,
		cdrTypeList,
		values...,
		nth<sizeof...(MergedTypes) - sizeof...(CarTypes)>(cdr)
	);
}

template <
	typename CAR,
	typename CDR
>
constexpr auto concatenate(const CAR& car, const CDR& cdr) {
	return concatenate(
		car,
		cdr,
		typename flatten_cons<CAR>::type(),
		typename flatten_cons<CDR>::type()
	);
}

}

#endif  // CONST_LIST_SRC_LIST_H_
