#include <gtest/gtest.h>
#include "fraction.h"
#include <cstdlib>


class FractionTest : public ::testing::Test {
	protected:
//		virtual void SetUp() {
//            _half = fraction::from_string("1/2");
//            _third = fraction::from_string("1/3");
//            _one = fraction::from_string("1");
//            _two = fraction::from_string("2");
//            _three = fraction::from_string("2");
//        }
//
//        fraction _half;
//        fraction _third;
//        fraction _one;
//        fraction _two;
//        fraction _three;
};


TEST_F(FractionTest, testCanonicalize) {
    fraction f1(40, -15);
    fraction f2(-40, 15);
    fraction f3(-8, 3);
    fraction f4(8, -3);

    ASSERT_EQ(f1.numerator(), -8);
    ASSERT_EQ(f2.numerator(), -8);
    ASSERT_EQ(f3.numerator(), -8);
    ASSERT_EQ(f4.numerator(), -8);

    ASSERT_EQ(f1.denominator(), 3);
    ASSERT_EQ(f2.denominator(), 3);
    ASSERT_EQ(f3.denominator(), 3);
    ASSERT_EQ(f4.denominator(), 3);
}

TEST_F(FractionTest, testFromString) {
    fraction f1(3, 4);
    fraction f2(-4, 5);

    fraction f3 = fraction::from_string("3/4");
    fraction f4 = fraction::from_string("-4/5");

    ASSERT_EQ(f1.numerator(), f3.numerator());
    ASSERT_EQ(f2.numerator(), f4.numerator());
    ASSERT_EQ(f1.denominator(), f3.denominator());
    ASSERT_EQ(f2.denominator(), f4.denominator());
}

TEST_F(FractionTest, testCopyConstructor) {
    fraction f1(24, 423);
    fraction f2{f1};
    fraction f3{f2};

    ASSERT_EQ(f1, f2);
    ASSERT_EQ(f1, f3);
}

TEST_F(FractionTest, testAssignmnent) {
    fraction f1(30, 241);

    fraction f2;
    f2 = f1;

    ASSERT_EQ(f1, f2);
}


///////////////////////////////////////////////
//  comparison


TEST_F(FractionTest, testLessEqual) {
    fraction f1(4, 1);
    fraction f2(5, 2);

    ASSERT_LE(f1, 10);
    ASSERT_LE(f1, 4);
    ASSERT_LE(f2, f1);
    ASSERT_LE(3, f1);
    ASSERT_LE(4, f1);

    ASSERT_FALSE(f1 <= 2);
    ASSERT_FALSE(f1 <= f2);
    ASSERT_FALSE(10 <= f1);
}

TEST_F(FractionTest, testLess) {}
TEST_F(FractionTest, testGreater) {}
TEST_F(FractionTest, testGreaterEqual) {}

TEST_F(FractionTest, testEqual) {
    fraction f1(3, 4);
    fraction f2(-4, 5);

    fraction f3 = fraction::from_string("3/4");
    fraction f4 = fraction::from_string("-4/5");

    ASSERT_TRUE(f1 == f1);
    ASSERT_TRUE(f2 == f2);
    ASSERT_TRUE(f3 == f3);
    ASSERT_TRUE(f4 == f4);

    ASSERT_TRUE(f1 == f3);
    ASSERT_TRUE(f2 == f4);

    ASSERT_FALSE(f1 == f2);
    ASSERT_FALSE(f1 == f4);
    ASSERT_FALSE(f2 == f3);
    ASSERT_FALSE(f3 == f4);

    fraction f5(3, 1);
    ASSERT_TRUE(f5 == 3);
    ASSERT_TRUE(3 == f5);
}

TEST_F(FractionTest, testNotEqual) {}

///////////////////////////////////////////////////
//TEST_F(FractionTest, testCopyConstructor) {}
//TEST_F(FractionTest, testCopyConstructor) {}
//TEST_F(FractionTest, testCopyConstructor) {}
//TEST_F(FractionTest, testCopyConstructor) {}
//TEST_F(FractionTest, testCopyConstructor) {}
//TEST_F(FractionTest, testCopyConstructor) {}
//TEST_F(FractionTest, testCopyConstructor) {}
//TEST_F(FractionTest, testCopyConstructor) {}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
