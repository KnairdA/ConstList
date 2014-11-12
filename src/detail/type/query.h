#ifndef CONST_LIST_SRC_DETAIL_TYPE_QUERY_H_
#define CONST_LIST_SRC_DETAIL_TYPE_QUERY_H_

#include <type_traits>

namespace ConstList {
namespace detail {

template <typename... Types>
struct VariadicTypeList {
	typedef VariadicTypeList type;

	static const std::size_t size = sizeof...(Types);
};


}
}

#endif  // CONST_LIST_SRC_DETAIL_TYPE_QUERY_H_
