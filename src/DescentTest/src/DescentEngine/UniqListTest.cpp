#include <DescentEngine/src/Util.h>

#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

TEST(UniqListTest, zero_erase) {
	std::list<int> myInt;

	// can only delete if not at the end already, needs to be checked here
	auto toRem = std::remove_if(myInt.begin(), myInt.end(), [](int & iRef) {return true;});
	myInt.erase(toRem, myInt.end());
}

TEST(UniqListTest, util_erase_if) {
	std::list<int> myInt;

	// should not crash
	util::erase_if(myInt, [](int & iRef) {return true;});

	myInt = { {1,2,3,4,5,6}};

	util::erase_if(myInt, [](int & iRef) {return (iRef % 2) == 0;});
	ASSERT_EQ(size_t(3), myInt.size());
}
