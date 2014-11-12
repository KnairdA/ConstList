#ifndef CONST_LIST_SRC_MAKE_H_
#define CONST_LIST_SRC_MAKE_H_

#include "detail/type/sfinae.h"
#include "detail/type/transformation.h"

namespace ConstList {

template <typename CAR>
constexpr auto make(const CAR& car) {
	return Cons<CAR, void>(car);
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
	typename CAR,
	typename CDR,
	detail::enable_if<!is_cons<CDR>::value> = 0
>
constexpr auto make(const CAR& car, const CDR& cdr) {
	return make(
		car,
		make<typename detail::replace_type<CAR, CDR>::type>(cdr)
	);
}

template <
	typename    CAR,
	typename... CDRs
>
constexpr auto make(const CAR& car, const CDRs&... cdrs) {
	return make(
		car,
		make<typename detail::replace_type<CAR, CDRs>::type...>(cdrs...)
	);
}


}

#endif  // CONST_LIST_SRC_MAKE_H_
