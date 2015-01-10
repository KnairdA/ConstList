#ifndef CONST_LIST_SRC_DETAIL_CONS_H_
#define CONST_LIST_SRC_DETAIL_CONS_H_

#include <utility>
#include <type_traits>

namespace ConstList {
namespace detail {

/*------------------------------------------------------------------------------
 All `CDR` template parameters of `Cons` must be derived from `detail::cons_tag`
 This is asserted through `detail::is_cons` throughout the whole implementation
 to reduce possible corner cases that would occur if one were allowed to pass
 arbitrary types as `CDR` types.

 i.e. an empty list / cons element is actually depicted as `ConsEmpty` or
 `Cons<void, void>` internally.
------------------------------------------------------------------------------*/

struct cons_tag{ };
struct ConsEmpty : cons_tag { };

template <typename Cons>
using is_cons = std::integral_constant<
	bool,
	std::is_base_of<cons_tag, Cons>::value
>;

template <typename Cons>
using is_empty_cons = std::integral_constant<
	bool,
	std::is_base_of<ConsEmpty, Cons>::value
>;

/*------------------------------------------------------------------------------
 Plain utility container for variadic parameter lists as required by `flatten_cons`.

 Currently this functionality is only used by `size` to read the size of a given
 `Cons` structure by querying the static `size` member of this class template.
------------------------------------------------------------------------------*/

template <typename... Types>
struct ConsTypeList {
	typedef ConsTypeList type;

	static const std::size_t size = sizeof...(Types);
};

/*------------------------------------------------------------------------------
 Implementations of the actual `Cons` functionality as selected based on the
 template parameters of `Cons` by `detail::select_cons`.

 Type equality of `CAR` and `CDR::car` is enforced to ensure type equality
 throughout the whole `Cons` structure / list. Otherwise this would be a tuple.
------------------------------------------------------------------------------*/

template <
	typename CAR,
	typename CDR
>
struct ConsWithCdr : cons_tag {
	static_assert(
		is_cons<CDR>::value,
		"CDR must be a instantiation of Cons"
	);

	static_assert(
		std::is_same<CAR, typename CDR::car_type>::value,
		"CAR type must be equal to CDR::car type"
	);

	typedef CAR car_type;
	typedef CDR cdr_type;

	ConsWithCdr(const CAR& value, const CDR& next):
		car{value},
		cdr{next} { }

	const CAR car;
	const CDR cdr;
};

template <typename CAR>
struct ConsWithoutCdr : cons_tag {
	typedef CAR       car_type;
	typedef ConsEmpty cdr_type;

	ConsWithoutCdr(const CAR& value):
		car{value},
		cdr{} { }

	const CAR       car;
	const ConsEmpty cdr;
};

/*------------------------------------------------------------------------------
 Selects the appropriate base class of `Cons`.

 Both `ConsWithoutCdr` and `ConsWithCdr` require `CAR` to be non-void.
 Void `CAR` automatically leads to `ConsEmpty` i.e. empty-list.
------------------------------------------------------------------------------*/

template <
	typename CAR,
	typename CDR
>
using select_cons = std::conditional<
	std::is_void<CAR>::value,
	ConsEmpty,
	typename std::conditional<
		std::is_void<CDR>::value,
		ConsWithoutCdr<CAR>,
		ConsWithCdr<CAR, CDR>
	>::type
>;

}
}

#endif  // CONST_LIST_SRC_DETAIL_CONS_H_
