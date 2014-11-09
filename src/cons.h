#ifndef CONST_LIST_SRC_CONS_H_
#define CONST_LIST_SRC_CONS_H_

#include <type_traits>
#include <utility>

namespace ConstList {

struct cons_tag{ };

template <typename Cons>
using is_cons = std::integral_constant<
	bool,
	std::is_base_of<cons_tag, Cons>::value
>;

template <
	typename CAR,
	typename CDR
>
struct ConsWithCdr : cons_tag {
	static_assert(
		is_cons<CDR>::value,
		"CDR must be a instantiation of Cons"
	);

	ConsWithCdr(const CAR& value, const CDR& next):
		car{value},
		cdr{next} { }

	const CAR car;
	const CDR cdr;
};

template <
	typename CAR
>
struct ConsWithoutCdr : cons_tag {
	ConsWithoutCdr(const CAR& value):
		car{value} { }

	const CAR car;
};

template <
	typename CAR,
	typename CDR
>
using select_cons = std::conditional<
	std::is_void<CDR>::value,
	ConsWithoutCdr<CAR>,
	ConsWithCdr<CAR, CDR>
>;

template <
	typename CAR,
	typename CDR
>
struct Cons : select_cons<CAR, CDR>::type {
	typedef typename select_cons<CAR, CDR>::type base;

	using base::base;
};

}

#endif  // CONST_LIST_SRC_CONS_H_
