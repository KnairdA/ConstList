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

TEST_F(ConstListTest, Size) {
	EXPECT_EQ(ConstList::size(ConstList::make(42)),                 1);
	EXPECT_EQ(ConstList::size(ConstList::make(42, 43)),             2);
	EXPECT_EQ(ConstList::size(ConstList::make(42, 43, 44, 45, 46)), 5);
}

TEST_F(ConstListTest, Head) {
	EXPECT_EQ(ConstList::head(ConstList::make(42)),                 42);
	EXPECT_EQ(ConstList::head(ConstList::make(42, 43)),             42);
	EXPECT_EQ(ConstList::head(ConstList::make(42, 43, 44, 45, 46)), 42);
}

TEST_F(ConstListTest, Tail) {
	EXPECT_EQ(ConstList::tail(ConstList::make(42, 43)).car,             43);
	EXPECT_EQ(ConstList::tail(ConstList::make(42, 43, 44, 45, 46)).car, 43);
}

TEST_F(ConstListTest, Nth) {
	EXPECT_EQ(ConstList::nth<0>(ConstList::make(42, 43, 44, 45, 46)), 42);
	EXPECT_EQ(ConstList::nth<1>(ConstList::make(42, 43, 44, 45, 46)), 43);
	EXPECT_EQ(ConstList::nth<2>(ConstList::make(42, 43, 44, 45, 46)), 44);
	EXPECT_EQ(ConstList::nth<3>(ConstList::make(42, 43, 44, 45, 46)), 45);
	EXPECT_EQ(ConstList::nth<4>(ConstList::make(42, 43, 44, 45, 46)), 46);
}

TEST_F(ConstListTest, Take) {
	EXPECT_EQ(ConstList::size(ConstList::take<1>(ConstList::make(42, 43, 44, 45, 46))), 1);
	EXPECT_EQ(ConstList::size(ConstList::take<2>(ConstList::make(42, 43, 44, 45, 46))), 2);
	EXPECT_EQ(ConstList::size(ConstList::take<3>(ConstList::make(42, 43, 44, 45, 46))), 3);
	EXPECT_EQ(ConstList::size(ConstList::take<4>(ConstList::make(42, 43, 44, 45, 46))), 4);
	EXPECT_EQ(ConstList::size(ConstList::take<5>(ConstList::make(42, 43, 44, 45, 46))), 5);

	EXPECT_EQ(ConstList::nth<0>(ConstList::take<3>(ConstList::make(42, 43, 44, 45, 46))), 42);
	EXPECT_EQ(ConstList::nth<1>(ConstList::take<3>(ConstList::make(42, 43, 44, 45, 46))), 43);
	EXPECT_EQ(ConstList::nth<2>(ConstList::take<3>(ConstList::make(42, 43, 44, 45, 46))), 44);
}

TEST_F(ConstListTest, Concatenate) {
	auto concatTest1 = ConstList::make(42)
	                 + ConstList::make(43);

	ASSERT_EQ(ConstList::size(concatTest1),    2);
	EXPECT_EQ(ConstList::nth<0>(concatTest1), 42);
	EXPECT_EQ(ConstList::nth<1>(concatTest1), 43);

	auto concatTest2 = ConstList::make(42, 43, 44, 45, 46)
	                 + ConstList::make(47, 48, 49, 50, 51, 52);

	ASSERT_EQ(ConstList::size(concatTest2),    11);
	EXPECT_EQ(ConstList::nth<0>(concatTest2),  42);
	EXPECT_EQ(ConstList::nth<4>(concatTest2),  46);
	EXPECT_EQ(ConstList::nth<5>(concatTest2),  47);
	EXPECT_EQ(ConstList::nth<10>(concatTest2), 52);

	auto concatTest3 = ConstList::make(42, 43, 44, 45, 46, 47)
	                 + ConstList::make(48, 49, 50, 51, 52);

	ASSERT_EQ(ConstList::size(concatTest3),    11);
	EXPECT_EQ(ConstList::nth<0>(concatTest3),  42);
	EXPECT_EQ(ConstList::nth<5>(concatTest3),  47);
	EXPECT_EQ(ConstList::nth<6>(concatTest3),  48);
	EXPECT_EQ(ConstList::nth<10>(concatTest3), 52);
}

TEST_F(ConstListTest, Foldr) {
	const int result{
		ConstList::foldr(
			ConstList::make(1, 2, 3, 4, 5),
			[](const int& x, const int& y) -> int {
				return x - y;
			},
			1
		)
	};

	EXPECT_EQ(result, 2);
}

TEST_F(ConstListTest, Map) {
	auto sourceList = ConstList::make(1, 2, 3, 4, 5);
	auto targetList = ConstList::map(
		sourceList,
		[](const int& x) -> int {
			return x * 2;
		}
	);

	ASSERT_EQ(ConstList::size(targetList),   5);
	EXPECT_EQ(ConstList::nth<0>(targetList), 2);
	EXPECT_EQ(ConstList::nth<1>(targetList), 4);
	EXPECT_EQ(ConstList::nth<2>(targetList), 6);
	EXPECT_EQ(ConstList::nth<3>(targetList), 8);
	EXPECT_EQ(ConstList::nth<4>(targetList), 10);
}

TEST_F(ConstListTest, Reverse) {
	auto descendingList = ConstList::reverse(
		ConstList::make(1, 2, 3, 4, 5)
	);

	ASSERT_EQ(ConstList::size(descendingList),   5);
	EXPECT_EQ(ConstList::nth<0>(descendingList), 5);
	EXPECT_EQ(ConstList::nth<1>(descendingList), 4);
	EXPECT_EQ(ConstList::nth<2>(descendingList), 3);
	EXPECT_EQ(ConstList::nth<3>(descendingList), 2);
	EXPECT_EQ(ConstList::nth<4>(descendingList), 1);
}

TEST_F(ConstListTest, Foldl) {
	const int result{
		ConstList::foldl(
			ConstList::make(1, 2, 3, 4, 5),
			[](const int& x, const int& y) -> int {
				return x - y;
			},
			1
		)
	};

	EXPECT_EQ(result, -14);
}

TEST_F(ConstListTest, Any) {
	auto list = ConstList::make(1, 2, 3, 4, 5);

	EXPECT_TRUE( ConstList::any(list, [](auto x) { return x % 2 == 0; }));
	EXPECT_TRUE( ConstList::any(list, [](auto x) { return x     >  0; }));
	EXPECT_TRUE( ConstList::any(list, [](auto x) { return x     == 5; }));
	EXPECT_FALSE(ConstList::any(list, [](auto x) { return x     == 6; }));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
