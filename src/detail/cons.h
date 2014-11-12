#ifndef CONST_LIST_SRC_DETAIL_CONS_H_
#define CONST_LIST_SRC_DETAIL_CONS_H_

#include <utility>
#include <type_traits>

namespace ConstList {
namespace detail {

struct cons_tag{ };

template <typename Cons>
using is_cons = std::integral_constant<
	bool,
	std::is_base_of<detail::cons_tag, Cons>::value
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

	static_assert(
		std::is_same<CAR, typename std::decay<decltype(CDR::car)>::type>::value,
		"CAR type must be equal to CDR::car type"
	);

	ConsWithCdr(const CAR& value, const CDR& next):
		car{value},
		cdr{next} { }

	const CAR car;
	const CDR cdr;
};

template <typename CAR>
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

}
}

#endif  // CONST_LIST_SRC_DETAIL_CONS_H_
