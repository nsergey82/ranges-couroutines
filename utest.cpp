//#include "fzbz_crtn.h"
//#include "fzbz_rng.h"
//#include "fzbz_rx.h"
//#include "fzbz_vanilla.h"
//#include <range/v3/all.hpp>
#include "gtest/gtest.h"

#include "count_record_breaking/count_record_breaking_vanilla.h"
#include "count_record_breaking/count_record_breaking_crtn.h"
#include "count_record_breaking/count_record_breaking_rx.h"
#include "count_record_breaking/count_record_breaking_rng.h"

TEST(RecordCounter, return_0_if_not_processed) {
    RecordCounter<int> best(11);
    EXPECT_EQ(0, best.get_count());
}

TEST(RecordCounter, return_0_if_first_not_greater_limit) {
    RecordCounter<int> best(11);
    best.process(11);
    EXPECT_EQ(0, best.get_count());
}

TEST(RecordCounter, return_1_if_first_greater_limit) {
    RecordCounter<int> best(11);
    best.process(12);
    EXPECT_EQ(1, best.get_count());
}

TEST(RecordCounter, return_1_if_2nd_greater_first) {
    RecordCounter<int> best(11);
    best.process(12);
    best.process(13);
    EXPECT_EQ(2, best.get_count());
}

TEST(RecordCounter, return_1_for_negated) {
    RecordCounter<int> best(-11);
    best.process(-10);
    EXPECT_EQ(1, best.get_count());
}

TEST(RecordCounter, return_2_with_skip) {
    RecordCounter<int> best(11);
    best.process(10);
    best.process(12);
    best.process(12);
    best.process(11);
    best.process(13);
    best.process(12);
    EXPECT_EQ(2, best.get_count());
}

TEST(RecordCounter, return_5_for_sequence) {
    RecordCounter<int> best(11);
    for(auto v : {1916, 4977, 6221, 8178, 4377, 6121, 7853, 7713, 7799, 8606})
        best.process(v);

    EXPECT_EQ(5, best.get_count());
}

TEST(RecordCounter, return_1_for_negated_sequence) {
    RecordCounter<int> best(-9999);
    for(auto v : {1916, 4977, 6221, 8178, 4377, 6121, 7853, 7713, 7799, 8606})
        best.process(-1 * v);

    EXPECT_EQ(1, best.get_count());
}

TEST(RecordCounter, return_6_for_normal_plus_negated_sequence) {
    RecordCounter<int> best(0);
    RecordCounter<int> worst(-9999);
    for(auto v : {1916, 4977, 6221, 8178, 4377, 6121, 7853, 7713, 7799, 8606}) {
        worst.process(-1 * v);
        best.process(v);
    }

    EXPECT_EQ(5+1, best.get_count()+worst.get_count());
}

TEST(TestCount, compare_vanilla_with_crtn) {
    for(unsigned i = 10; i < 100; ++i) {
        EXPECT_EQ(crtn::count_breaking_record_crtn(i),
                  count_breaking_record_vanilla(i));
    }
}

TEST(TestCount, compare_vanilla_with_rx) {
    for(unsigned i = 10; i < 100; ++i) {
        EXPECT_EQ(rx::count_breaking_record_rx(i),
                  count_breaking_record_vanilla(i));
    }
}

TEST(T1, t) {
    test(5);
}

//TEST(TestVanilla, Size_of_vector_eq_limit_minus_1)
//{
//    EXPECT_TRUE(vanilla::fizbuz(1).empty());
//    EXPECT_EQ(3, vanilla::fizbuz(4).size()); //1,2,3
//    EXPECT_EQ(21, vanilla::fizbuz(22).size());
//    EXPECT_EQ(21, vanilla::fizbuz_mod(22).size());
//    EXPECT_EQ(21, vanilla::fizbuz_transform(22).size());
//}
//
//TEST(TestVanilla, First_33_vals_match)
//{
//    const auto m = helper::marker;
//    unsigned expected[] = {   1,   2, m+3,   4, m+5,  //  5
//                            m+3,   7,   8, m+3, m+5,  // 10
//                             11, m+3,  13,  14, m+15, // 15
//                             16,  17, m+3,  19, m+5,  // 20
//                            m+3,  22,  23, m+3, m+5,  // 25
//                             26, m+3,  28,  29, m+15, // 30
//                             31,  32, m+3 };
//
//    auto no_mod = std::equal(std::begin(expected),std::end(expected),
//                             vanilla::fizbuz(34).cbegin());
//    auto mod = std::equal(std::begin(expected),std::end(expected),
//                          vanilla::fizbuz_mod(34).cbegin());
//    auto transfrm = std::equal(std::begin(expected),std::end(expected),
//                               vanilla::fizbuz_transform(34).cbegin());
//    auto transfrm_s = std::equal(std::begin(expected),std::end(expected),
//                               vanilla::fizbuz_transform_slow(34).cbegin());
//    EXPECT_TRUE(no_mod);
//    EXPECT_TRUE(mod);
//    EXPECT_TRUE(transfrm);
//    EXPECT_TRUE(transfrm_s);
//}
//
//TEST(TestRng, Validate_fizbuz)
//{
//    const unsigned times = 1987;
//    EXPECT_EQ(rng::fizbuz(times), vanilla::fizbuz(times));
//    EXPECT_EQ(brng::fizbuz(times), vanilla::fizbuz(times));
//    EXPECT_EQ(rx::fizbuz(times), vanilla::fizbuz(times));
//    EXPECT_EQ(crtn::fizbuz(times), vanilla::fizbuz(times));
//}
//
//TEST(TestRng, Validate_fizbuz_str)
//{
//    const unsigned times = 1234;
//    const auto acc = rng::fizbuz_str(times);
//    EXPECT_EQ(acc, brng::fizbuz_str(times));
//    EXPECT_EQ(acc, rx::fizbuz_str(times));
//    EXPECT_EQ(acc, crtn::fizbuz_str(times));
//}


