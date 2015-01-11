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
	EXPECT_EQ(ConstList::size(ConstList::take<9>(ConstList::make(42, 43, 44, 45, 46))), 5);

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

TEST_F(ConstListTest, FizzBuzzMap) {
	auto list = ConstList::map(
		ConstList::make(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15),
		[](const int& x) -> std::string {
			std::string output{};

			if ( x % 3 == 0 ) {
				output += "Fizz";
			}

			if ( x % 5 == 0 ) {
				output += "Buzz";
			}

			if ( output.empty() ) {
				output += std::to_string(x);
			}

			return output;
		}
	);

	EXPECT_EQ(ConstList::nth<0>(list),  "1");
	EXPECT_EQ(ConstList::nth<1>(list),  "2");
	EXPECT_EQ(ConstList::nth<2>(list),  "Fizz");
	EXPECT_EQ(ConstList::nth<3>(list),  "4");
	EXPECT_EQ(ConstList::nth<4>(list),  "Buzz");
	EXPECT_EQ(ConstList::nth<5>(list),  "Fizz");
	EXPECT_EQ(ConstList::nth<6>(list),  "7");
	EXPECT_EQ(ConstList::nth<7>(list),  "8");
	EXPECT_EQ(ConstList::nth<8>(list),  "Fizz");
	EXPECT_EQ(ConstList::nth<9>(list),  "Buzz");
	EXPECT_EQ(ConstList::nth<10>(list), "11");
	EXPECT_EQ(ConstList::nth<11>(list), "Fizz");
	EXPECT_EQ(ConstList::nth<12>(list), "13");
	EXPECT_EQ(ConstList::nth<13>(list), "14");
	EXPECT_EQ(ConstList::nth<14>(list), "FizzBuzz");
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

TEST_F(ConstListTest, All) {
	auto list = ConstList::make(1, 2, 3, 4, 5);

	EXPECT_TRUE( ConstList::all(list, [](auto x) { return x     >  0; }));
	EXPECT_FALSE(ConstList::all(list, [](auto x) { return x % 2 == 0; }));
}

TEST_F(ConstListTest, None) {
	auto list = ConstList::make(1, 2, 3, 4, 5);

	EXPECT_TRUE( ConstList::none(list, [](auto x) { return x     >  6; }));
	EXPECT_FALSE(ConstList::none(list, [](auto x) { return x     >  0; }));
	EXPECT_FALSE(ConstList::none(list, [](auto x) { return x % 2 == 0; }));
}

TEST_F(ConstListTest, Count) {
	const std::size_t evenCount{
		ConstList::count(
			ConstList::make(1, 2, 3, 4, 5),
			[](auto x) { return x % 2 == 0; }
		)
	};

	EXPECT_EQ(evenCount, 2);

	const std::size_t fullCount{
		ConstList::count(
			ConstList::make(1, 2, 3, 4, 5),
			[](auto x) { return x > 0; }
		)
	};

	EXPECT_EQ(fullCount, 5);

	const std::size_t noneCount{
		ConstList::count(
			ConstList::make(1, 2, 3, 4, 5),
			[](auto x) { return x > 5; }
		)
	};

	EXPECT_EQ(noneCount, 0);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
