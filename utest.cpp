#include "fzbz_crtn.h"
#include "fzbz_rng.h"
#include "fzbz_rx.h"
#include "fzbz_vanilla.h"

#include "gtest/gtest.h"

TEST(TestVanilla, Size_of_vector_eq_limit_minus_1)
{
    EXPECT_TRUE(vanilla::fizbuz(1).empty());
    EXPECT_EQ(3, vanilla::fizbuz(4).size()); //1,2,3
    EXPECT_EQ(21, vanilla::fizbuz(22).size());
    EXPECT_EQ(21, vanilla::fizbuz_mod(22).size());
    EXPECT_EQ(21, vanilla::fizbuz_transform(22).size());
}

TEST(TestVanilla, First_33_vals_match)
{
    const auto m = helper::marker;
    unsigned expected[] = {   1,   2, m+3,   4, m+5,  //  5
                            m+3,   7,   8, m+3, m+5,  // 10
                             11, m+3,  13,  14, m+15, // 15
                             16,  17, m+3,  19, m+5,  // 20
                            m+3,  22,  23, m+3, m+5,  // 25
                             26, m+3,  28,  29, m+15, // 30
                             31,  32, m+3 };

    auto no_mod = std::equal(std::begin(expected),std::end(expected),
                             vanilla::fizbuz(34).cbegin());
    auto mod = std::equal(std::begin(expected),std::end(expected),
                          vanilla::fizbuz_mod(34).cbegin());
    auto transfrm = std::equal(std::begin(expected),std::end(expected),
                               vanilla::fizbuz_transform(34).cbegin());
    auto transfrm_s = std::equal(std::begin(expected),std::end(expected),
                               vanilla::fizbuz_transform_slow(34).cbegin());
    EXPECT_TRUE(no_mod);
    EXPECT_TRUE(mod);
    EXPECT_TRUE(transfrm);
    EXPECT_TRUE(transfrm_s);
}

TEST(TestRng, Validate_fizbuz)
{
    const unsigned times = 1987;
    EXPECT_EQ(rng::fizbuz(times), vanilla::fizbuz(times));
    EXPECT_EQ(brng::fizbuz(times), vanilla::fizbuz(times));
    EXPECT_EQ(rx::fizbuz(times), vanilla::fizbuz(times));
    EXPECT_EQ(crtn::fizbuz(times), vanilla::fizbuz(times));
}

TEST(TestRng, Validate_fizbuz_str)
{
    const unsigned times = 1234;
    const auto acc = rng::fizbuz_str(times);
    EXPECT_EQ(acc, brng::fizbuz_str(times));
    EXPECT_EQ(acc, rx::fizbuz_str(times));
    EXPECT_EQ(acc, crtn::fizbuz_str(times));
}