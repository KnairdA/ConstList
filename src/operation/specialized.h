#ifndef CONST_LIST_SRC_OPERATION_SPECIALIZED_H_
#define CONST_LIST_SRC_OPERATION_SPECIALIZED_H_

#include <cons.h>
#include <make.h>

#include "higher.h"
#include "concatenate.h"

namespace ConstList {

template <typename Cons>
constexpr auto reverse(const Cons& cons) {
	return foldr(
		cons,
		[](auto car, auto cdr) {
			return concatenate(cdr, make(car));
		},
		make()
	);
}

}

#endif  // CONST_LIST_SRC_OPERATION_SPECIALIZED_H_
