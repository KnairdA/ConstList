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

}
}

#endif  // CONST_LIST_SRC_DETAIL_TYPE_TRANSFORMATION_H_
