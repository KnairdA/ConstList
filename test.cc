#include <cstdint>

#include "list.h"

int main(int, char**) {
	auto list = ConstList::make<std::uint8_t>(42, 43, 44, 45, 46);

	return ConstList::nth<2>(
		ConstList::take<3>(list)
	);
}
