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
	auto concatTest1 = ConstList::concatenate(
		ConstList::make(42),
		ConstList::make(43)
	);

	EXPECT_EQ(ConstList::size(concatTest1), 2);
	EXPECT_EQ(ConstList::nth<0>(concatTest1), 42);
	EXPECT_EQ(ConstList::nth<1>(concatTest1), 43);

	auto concatTest2 = ConstList::concatenate(
		ConstList::make(42, 43, 44, 45, 46),
		ConstList::make(47, 48, 49, 50, 51, 52)
	);

	EXPECT_EQ(ConstList::size(concatTest2), 11);
	EXPECT_EQ(ConstList::nth<0>(concatTest2), 42);
	EXPECT_EQ(ConstList::nth<4>(concatTest2), 46);
	EXPECT_EQ(ConstList::nth<5>(concatTest2), 47);
	EXPECT_EQ(ConstList::nth<10>(concatTest2), 52);

	auto concatTest3 = ConstList::concatenate(
		ConstList::make(42, 43, 44, 45, 46, 47),
		ConstList::make(48, 49, 50, 51, 52)
	);

	EXPECT_EQ(ConstList::size(concatTest3), 11);
	EXPECT_EQ(ConstList::nth<0>(concatTest3), 42);
	EXPECT_EQ(ConstList::nth<5>(concatTest3), 47);
	EXPECT_EQ(ConstList::nth<6>(concatTest3), 48);
	EXPECT_EQ(ConstList::nth<10>(concatTest3), 52);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
