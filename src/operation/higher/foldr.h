#ifndef CONST_LIST_SRC_OPERATION_HIGHER_FOLDR_H_
#define CONST_LIST_SRC_OPERATION_HIGHER_FOLDR_H_

#include <cons.h>
#include <make.h>
#include <detail/type/sfinae.h>
#include <operation/concatenate.h>

namespace ConstList {

template <
	typename Cons,
	typename Function,
	typename Intitial,
	detail::enable_if<is_empty_cons<Cons>::value> = 0
>
constexpr auto foldr(const Cons&, const Function&, const Intitial& initial) {
	return initial;
}

template <
	typename Cons,
	typename Function,
	typename Intitial,
	detail::enable_if<!is_empty_cons<Cons>::value> = 0
>
constexpr auto foldr(
	const Cons&     cons,
	const Function& function,
	const Intitial& initial
) {
	return function(
		cons.car,
		foldr(cons.cdr, function, initial)
	);
}

}


#endif  // CONST_LIST_SRC_OPERATION_HIGHER_FOLDR_H_
