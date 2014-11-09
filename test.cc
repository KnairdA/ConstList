#include "list.h"

int main(int, char**) {
	auto list = ConstList::make(42, 43, 44, 45, 46);

	return ConstList::nth<3>(list);
}
