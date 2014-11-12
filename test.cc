#include "gtest/gtest.h"

#include <cstdint>

#include "list.h"

class ConstListTest : public ::testing::Test {
	public:
		template <typename Type>
		using expected_type = ConstList::Cons<
			Type,
			ConstList::Cons<
				Type,
				ConstList::Cons<
					Type,
					ConstList::Cons<
						Type,
						ConstList::Cons<
							Type,
							void
						>
					>
				>
			>
		>;

};

TEST_F(ConstListTest, Make) {
	ASSERT_TRUE((std::is_same<
		decltype(ConstList::make(42)),
		ConstList::Cons<int, void>
	>::value));

	ASSERT_TRUE((std::is_same<
		decltype(ConstList::make(42, 43)),
		ConstList::Cons<int, ConstList::Cons<int, void>>
	>::value));

	ASSERT_TRUE((std::is_same<
		decltype(ConstList::make<std::uint64_t>(42)),
		ConstList::Cons<std::uint64_t, void>
	>::value));

	ASSERT_TRUE((std::is_same<
		decltype(ConstList::make<std::uint64_t>(42, 43)),
		ConstList::Cons<std::uint64_t, ConstList::Cons<std::uint64_t, void>>
	>::value));

	ASSERT_TRUE((std::is_same<
		decltype(ConstList::make(42, 43, 44, 45, 46)),
		expected_type<int>
	>::value));

	ASSERT_TRUE((std::is_same<
		decltype(ConstList::make<std::uint8_t>(42, 43, 44, 45, 46)),
		expected_type<std::uint8_t>
	>::value));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
