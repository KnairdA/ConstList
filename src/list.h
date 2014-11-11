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
	return cons.car;
}

template <typename Cons>
constexpr auto tail(const Cons& cons) {
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
	return detail::size(typename detail::flatten_cons<Cons>::type());
}

}

#endif  // CONST_LIST_SRC_LIST_H_
