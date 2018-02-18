#include <gtest/gtest.h>
#include <cstdlib>
#include "bst.h"
#include <random>
#include <algorithm>

template <class T>
std::ostream& operator << (std::ostream& str, const std::vector<T>& vec) {
    str << "[ ";
    for(auto x : vec) {
        str << x << " ";
    }
    str << "]";
    return str;
}


class TreeTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        random_vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        shuffle (random_vector.begin(), random_vector.end(),
                 std::default_random_engine(0));
    }

    virtual void TearDown() {}

    BST<int> tree1;
    std::vector<int> random_vector;
};


TEST_F(TreeTest, TestInsert) {
    for(auto x : random_vector) {
        tree1.insert(x);
    }
    ASSERT_EQ(tree1.size(), random_vector.size());
}

TEST_F(TreeTest, TestRemove) {
    for(auto x : random_vector) {
        tree1.insert(x);
    }

    for(int i = 1000; i < 1100; ++i) {
        ASSERT_FALSE(tree1.remove(i));
    }

    for(auto x : random_vector) {
        ASSERT_TRUE(tree1.remove(x));
    }

    ASSERT_EQ(tree1.size(), 0);
}

TEST_F(TreeTest, TestPopMin) {
    for(auto x : random_vector) {
        tree1.insert(x);
    }

    int initial_size = tree1.size();

    int min = tree1.pop_min();
    int true_min = *std::min_element(random_vector.begin(),
                                    random_vector.end());
    ASSERT_EQ(min, true_min);
    ASSERT_EQ(tree1.size(), initial_size - 1);
    ASSERT_FALSE(tree1.remove(min));
}

TEST_F(TreeTest, TestPopMax) {
    for(auto x : random_vector) {
        tree1.insert(x);
    }

    int initial_size = tree1.size();

    int true_max = *std::max_element(random_vector.begin(),
                                    random_vector.end());
    int max = tree1.pop_max();
    ASSERT_EQ(max, true_max);
    ASSERT_EQ(tree1.size(), initial_size - 1);
    ASSERT_FALSE(tree1.remove(max));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
