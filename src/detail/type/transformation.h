#ifndef CONST_LIST_SRC_DETAIL_TYPE_TRANSFORMATION_H_
#define CONST_LIST_SRC_DETAIL_TYPE_TRANSFORMATION_H_

#include <type_traits>

namespace ConstList {
namespace detail {

template <
	typename Target,
	typename Source
>
struct replace_type {
	static_assert(
		std::is_convertible<Source, Target>::value,
		"Type equality demands convertability"
	);

	typedef Target type;
};

template <typename... Types>
struct flattened_cons {
	typedef flattened_cons type;
};

template <
	typename    Cons,
	typename... Current
>
struct flatten_cons {
	typedef typename std::conditional<
		std::is_void<typename Cons::cdr_type>::value,
		flattened_cons<                       Current..., typename Cons::car_type>,
		flatten_cons<typename Cons::cdr_type, Current..., typename Cons::car_type>
	>::type::type type;
};

}
}

#endif  // CONST_LIST_SRC_DETAIL_TYPE_TRANSFORMATION_H_
