#include <gtest/gtest.h>
#include "fraction.h"
#include <cstdlib>


class FractionTest : public ::testing::Test {
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
    fraction f2(f1);
    fraction f3(f2);

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

TEST_F(FractionTest, testNotEqual) {
    fraction f1(3, 4);
    fraction f2(-4, 5);

    fraction f3 = fraction::from_string("3/4");
    fraction f4 = fraction::from_string("-4/5");

    ASSERT_NE(f1, f2);
    ASSERT_NE(f1, f4);
    ASSERT_NE(f2, f3);
    ASSERT_NE(f3, f4);

    ASSERT_FALSE(f1 != f1);
    ASSERT_FALSE(f1 != f3);
    ASSERT_FALSE(f2 != f2);
    ASSERT_FALSE(f2 != f4);

    ASSERT_NE(f1, 1);
    ASSERT_FALSE(fraction(3, 1) != 3);
}

////////////////////////////////////////////
// arithmetics

TEST_F(FractionTest, testMul) {
    fraction f1(5, 12);
    fraction f2(2, 5);

    ASSERT_EQ(2 * f1 * 3 * f2, fraction(1, 1));

    f1 *= 12;
    f1 *= f2;

    ASSERT_EQ(f1, 2);
}

TEST_F(FractionTest, testDiv) {
    fraction f1(4, 1);
    fraction f2(2, 7);

    ASSERT_EQ(2 / (f1 / f2 / 7), 1);

    f1 /= 2;
    f1 /= f2;

    ASSERT_EQ(f1, 7);
}

TEST_F(FractionTest, testAdd) {
    fraction f1(1, 3);
    fraction f2(1, 4);
    fraction f3(5, 12);

    ASSERT_EQ(1 + f1 + f2 + f3, 2);

    f1 += f1;
    f1 += 1;

    ASSERT_EQ(f1, fraction(5, 3));
}

TEST_F(FractionTest, testSub) {
    fraction f1(2, 3);
    fraction f2(1, 3);

    ASSERT_EQ(5 - f1 - f2 - 3, 1);

    f1 -= f2;
    f1 -= 1;

    ASSERT_EQ(f1, fraction(-2, 3));
}


///////////////////////////////////////////
// other

TEST_F(FractionTest, testInvert) {
    fraction f1(2, 3);
    fraction f2(3, 2);

    ASSERT_EQ(!f1, f2);
    ASSERT_EQ(!!f1, f1);
}

TEST_F(FractionTest, testNegate) {
    fraction f1(2, 3);
    fraction f2(-2, 3);

    ASSERT_EQ(f1, -f2);
    ASSERT_EQ(-f1, f2);
    ASSERT_EQ(-(-f1), f1);
}

TEST_F(FractionTest, testFromStream) {
    std::istringstream str("1/2");
    std::istringstream str2("-1/2");
    std::istringstream str3("-1//2");
    std::istringstream str4("-1\\2");
    std::istringstream str5("1/0");

    fraction f;

    str >> f;
    ASSERT_EQ(f, fraction(1, 2));

    str2>> f;
    ASSERT_EQ(f, fraction(-1, 2));

    ASSERT_ANY_THROW(str3 >> f);
    ASSERT_ANY_THROW(str4 >> f);
    ASSERT_THROW(str5 >> f, ZeroDivision);
}

TEST_F(FractionTest, testToStream) {
    fraction f(-3, 4);
    std::ostringstream str;

    str << f;

    ASSERT_EQ(str.str(), "-3/4");
}

TEST_F(FractionTest, testFromToStreamPersistence) {
    fraction f(-3, 4);
    fraction f1(0, 1);
    std::ostringstream ostr;
    std::istringstream istr;

    ostr << f;
    istr.str(ostr.str());
    istr >> f1;

    ASSERT_EQ(f1, f);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
