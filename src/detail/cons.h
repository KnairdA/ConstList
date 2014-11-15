#ifndef CONST_LIST_SRC_DETAIL_CONS_H_
#define CONST_LIST_SRC_DETAIL_CONS_H_

#include <utility>
#include <type_traits>

namespace ConstList {
namespace detail {

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
