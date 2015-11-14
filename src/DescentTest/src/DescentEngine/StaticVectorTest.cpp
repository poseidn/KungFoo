#include <gtest/gtest.h>

#include <DescentEngine/src/DataTypes/StaticVector.h>

TEST(StaticVectorTest, push_get) {
	StaticVector<int> sVect;

	auto ref1 = sVect.push_back(23);
	auto ref2 = sVect.push_back(24);
	auto ref3 = sVect.push_back(25);

	ASSERT_EQ(23, ref1.get());
	ASSERT_EQ(24, ref2.get());
	ASSERT_EQ(25, ref3.get());

	ASSERT_EQ(size_t(3), sVect.activeSize());

	sVect.remove(ref2);

	ASSERT_EQ(size_t(2), sVect.activeSize());

	auto ref4 = sVect.push_back(45);
	ASSERT_EQ(int(45), ref4.get());
	ASSERT_EQ(size_t(3), sVect.activeSize());

	auto findInsert = [] ( int const& it ) -> bool {return it > 30;};
	auto ref5 = sVect.push(55, findInsert);
	ASSERT_EQ(int(55), ref5.get());

	// we expect it at positon 2
	ASSERT_EQ(int(55), sVect.get(2));
	ASSERT_EQ(int(45), sVect.get(3));

}

