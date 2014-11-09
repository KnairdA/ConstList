#ifndef CONST_LIST_SRC_MAKE_H_
#define CONST_LIST_SRC_MAKE_H_

#include "detail/sfinae.h"

namespace ConstList {

template <typename CAR>
constexpr auto make(const CAR& car) {
	return Cons<CAR, void>(car);
}

template <
	typename CAR,
	typename CDR,
	detail::enable_if<!is_cons<CDR>::value> = 0
>
constexpr auto make(const CAR& car, const CDR& cdr) {
	return Cons<CAR, decltype(make(cdr))>(
		car,
		make(cdr)
	);
}

template <
	typename CAR,
	typename CDR,
	detail::enable_if<is_cons<CDR>::value> = 0
>
constexpr auto make(const CAR& car, const CDR& cdr) {
	return Cons<CAR, CDR>(car, cdr);
}

template <
	typename    CAR,
	typename... CDRs
>
constexpr auto make(const CAR& car, const CDRs&... cdrs) {
	return make(
		car,
		make<CDRs...>(cdrs...)
	);
}


}

#endif  // CONST_LIST_SRC_MAKE_H_
