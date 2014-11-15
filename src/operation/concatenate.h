#ifndef CONST_LIST_SRC_OPERATION_CONCATENATE_H_
#define CONST_LIST_SRC_OPERATION_CONCATENATE_H_

#include <cons.h>
#include <make.h>
#include <detail/type/sfinae.h>

namespace ConstList {

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

}

#endif  // CONST_LIST_SRC_OPERATION_CONCATENATE_H_
