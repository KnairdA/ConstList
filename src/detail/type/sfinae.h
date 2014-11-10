#ifndef CONST_LIST_SRC_DETAIL_TYPE_SFINAE_H_
#define CONST_LIST_SRC_DETAIL_TYPE_SFINAE_H_

#include <type_traits>

namespace ConstList {
namespace detail {

template <bool Condition>
using enable_if = typename std::enable_if<Condition, std::size_t>::type;


}
}

#endif  // CONST_LIST_SRC_DETAIL_TYPE_SFINAE_H_
