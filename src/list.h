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

}

#endif  // CONST_LIST_SRC_LIST_H_
