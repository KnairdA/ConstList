#ifndef CONST_LIST_SRC_MAKE_H_
#define CONST_LIST_SRC_MAKE_H_

#include "detail/type/sfinae.h"

namespace ConstList {

namespace detail {

/*------------------------------------------------------------------------------
 Enforces all types of a `Cons` structure to be equal to the first `CAR` type
 by replacing i.e. _unifying_ them.

 This is implemented using a helper template as usage in a variadic template
 context (e.g. the variadic `make` overload) would be impossible otherwise as
 there would be no resolvable connection between the variadic parameter pack and
 the `Target` type.
------------------------------------------------------------------------------*/

template <
	typename Target,
	typename Source
>
struct unify_type {
	static_assert(
		std::is_convertible<Source, Target>::value,
		"Type equality demands convertability"
	);

	typedef Target type;
};

}

/*------------------------------------------------------------------------------
 Special case overload to support construction of empty lists using `make`
------------------------------------------------------------------------------*/

constexpr Cons<void, void> make() {
	return Cons<void, void>();
}

/*------------------------------------------------------------------------------
 Special case / terminating overload to support construction of single value lists

 e.g. the last element of a list
------------------------------------------------------------------------------*/

template <typename CAR>
constexpr auto make(const CAR& car) {
	return Cons<CAR, void>(car);
}

/*------------------------------------------------------------------------------
 Overload to construct a `Cons` consisting of a value and another `Cons` type.

 This is required to enable the implementation of the variadic parameter pack
 resolution terminating `make` overload in terms of another `make` call.
------------------------------------------------------------------------------*/

template <
	typename CAR,
	typename CDR,
	detail::enable_if<is_cons<CDR>::value> = 0
>
constexpr auto make(const CAR& car, const CDR& cdr) {
	return Cons<CAR, CDR>(car, cdr);
}

/*------------------------------------------------------------------------------
 Terminating overload of recursive variadic parameter pack resolution.
 Also the overload of choice for construction of two-element lists.

 i.e. the recursion exit-condition requires `CDR` to be non-cons
 i.e. `CDR` must be a normal non-void and non-cons type
       (void is already handled by a special purpose `make` overload)
------------------------------------------------------------------------------*/

template <
	typename CAR,
	typename CDR,
	detail::enable_if<!is_cons<CDR>::value> = 0
>
constexpr auto make(const CAR& car, const CDR& cdr) {
	return make(
		car,
		make<typename detail::unify_type<CAR, CDR>::type>(cdr)
	);
}

/*------------------------------------------------------------------------------
 Basic recursive traversion `make` overload for construction of lists with a
 length greater than two. Terminates on the last value pair.

 One may explicitly declare the first type (i.e. `CAR`) to enforce a type
 different from the one deduced by the compiler:

 `make<std::uint8_t>(1, 2, 3, 4)` => `Cons<std::uint8_t, Cons<std::uint8_t...`
------------------------------------------------------------------------------*/

template <
	typename    CAR,
	typename... CDRs
>
constexpr auto make(const CAR& car, const CDRs&... cdrs) {
	return make(
		car,
		make<typename detail::unify_type<CAR, CDRs>::type...>(cdrs...)
	);
}

}

#endif  // CONST_LIST_SRC_MAKE_H_
