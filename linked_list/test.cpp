#include <gtest/gtest.h>
#include "linkedlist.hpp"
#include <cstdlib>


using namespace LList;

class ListTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		// virtual void TearDown() {}

        LinkedList<double> _list1;
        LinkedList<double> _list2;
};

TEST_F(ListTest, testListEmptyByDefault) {
    ASSERT_EQ(_list1.size(), 0);
    ASSERT_TRUE(_list1.empty());
}

/////////////////////////////////////////
// push and pop

TEST_F(ListTest, testListPushBack) {
    ASSERT_EQ(_list1.size(), 0);
    _list1.push_back(12);
    _list1.push_back(2);
    _list1.push_back(1);
    ASSERT_EQ(_list1.size(), 3);
}

TEST_F(ListTest, testListPopBack) {
    _list1.push_back(1);
    _list1.push_back(2);
    _list1.push_back(3);
    ASSERT_EQ(_list1.size(), 3);
    EXPECT_EQ(_list1.pop_back(), 3);
    EXPECT_EQ(_list1.pop_back(), 2);
    EXPECT_EQ(_list1.pop_back(), 1);
}

TEST_F(ListTest, testListPushFront) {
    ASSERT_EQ(_list1.size(), 0);
    _list1.push_front(12);
    _list1.push_front(2);
    _list1.push_front(1);
    ASSERT_EQ(_list1.size(), 3);
}

TEST_F(ListTest, testListPopFront) {
    _list1.push_front(1);
    _list1.push_front(2);
    _list1.push_front(3);
    EXPECT_EQ(_list1.size(), 3);
    EXPECT_EQ(_list1.pop_front(), 3);
    EXPECT_EQ(_list1.pop_front(), 2);
    EXPECT_EQ(_list1.pop_front(), 1);
}

TEST_F(ListTest, testPushAndPopPreservesOrder) {
    _list1.push_front(1);
    _list1.push_front(2);
    EXPECT_EQ(_list1.pop_back(), 1);
    _list1.push_back(3);
    EXPECT_EQ(_list1.pop_front(), 2);
    EXPECT_EQ(_list1.pop_back(), 3);
}

TEST_F(ListTest, testPopMakesListEmpty) {
    for(int i = 0; i < 10; ++i) {
        _list1.push_back(1);
        _list1.push_front(2);
    }

    for(int i = 0; i < 10; ++i) {
        _list1.pop_back();
        _list1.pop_front();
    }

    ASSERT_EQ(_list1.size(), 0);
    ASSERT_TRUE(_list1.empty());
}

TEST_F(ListTest, testPopFrontThrowsIfEmpty) {
    ASSERT_THROW(_list1.pop_front(), EmptyList);
}

TEST_F(ListTest, testPopBackThrowsIfEmpty) {
    ASSERT_THROW(_list1.pop_back(), EmptyList);
}

//////////////////////////////////////
// front and back

TEST_F(ListTest, testFrontWorks) {
    _list1.push_front(13);
    _list1.push_back(1);
    ASSERT_EQ(_list1.front(), 13);
}

TEST_F(ListTest, testFrontThrowsIfEmpty) {
    ASSERT_THROW(_list1.front(), EmptyList);
}

TEST_F(ListTest, testBackWorks) {
    _list1.push_back(23);
    _list1.push_back(108);
    ASSERT_EQ(_list1.back(), 108);
}

TEST_F(ListTest, testBackThrowsIfEmpty) {
    ASSERT_THROW(_list1.back(), EmptyList);
}

//////////////////////////////////////
// find, delete

TEST_F(ListTest, testFindWorks) { 
    double inserted_val = 4123.5;
    for(int i = 0; i < 10; ++i) {
        _list1.push_front(rand() % 1000);
        _list1.push_back(rand() % 1000);
    }

    _list1.push_back(inserted_val);

    for(int i = 0; i < 10; ++i) {
        _list1.push_front(rand() % 1000);
        _list1.push_back(rand() % 1000);
    }

    auto found = _list1.find([&](const double& v) {
                return v == inserted_val;
            });

    ASSERT_EQ(found.second, inserted_val);

    found = _list1.find([](const double& v) {
                return v > 1000;
            });

    ASSERT_EQ(found.second, inserted_val);
}

TEST_F(ListTest, testFindThrowsNotFound) {
    double not_inserted_val = 4123.5;

    for(int i = 0; i < 10; ++i) {
        _list1.push_front(rand() % 1000);
        _list1.push_back(rand() % 1000);
    }

    for(int i = 0; i < 10; ++i) {
        _list1.push_front(rand() % 1000);
        _list1.push_back(rand() % 1000);
    }

    ASSERT_THROW(
        _list1.find([&](const double& v) {
            return v == not_inserted_val;
        }),
        NotFound
    );

    ASSERT_THROW(
        _list1.find([](const double& v) {
            return v > 1000;
        }),
        NotFound
    );
}

TEST_F(ListTest, testFindIsOfLinearComplexity) { }
TEST_F(ListTest, testFindAndDelWorks) { }
TEST_F(ListTest, testFindAndDelThrowsUnlessFound) { }
TEST_F(ListTest, testFindApplyWorks) { }
TEST_F(ListTest, testFindForEachWorks) { }
TEST_F(ListTest, testFindForAcceptsClosures) { }

///////////////////////////////////////


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
