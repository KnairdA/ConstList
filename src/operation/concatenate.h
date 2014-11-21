#ifndef CONST_LIST_SRC_OPERATION_CONCATENATE_H_
#define CONST_LIST_SRC_OPERATION_CONCATENATE_H_

#include <cons.h>
#include <make.h>
#include <detail/type/sfinae.h>

namespace ConstList {

/*------------------------------------------------------------------------------
 Special case overload handling the concatenation of an empty `CAR` and
 non-empty `CDR` element.

 This is required to enable concatenation from inside methods called by higher-
 order methods such as `foldr` in a generalized fashion. Otherwise special case
 handling for empty list initial values would be required.
------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------
 Special case overload handling the concatenation of an non-empty `CAR` and
 empty `CDR` element.

 This is required because of the same reasons as the empty + non-empty special
 case overload.
------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------
 Terminating overload of `concatenate`.

 Recursive concatenation terminates on the last cons pair as it is easily
 constructed using `make`.
------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------
 Basic recursive overload of `concatenate`.

 Only the `CAR` cons structure has to be reconstructed as `CDR` may be simply
 appended to its end. Reconstruction is required because of the constant nature
 of `Cons`.
------------------------------------------------------------------------------*/

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
