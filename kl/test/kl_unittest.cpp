/*************************************************************************
	> File Name: kl_unittest.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Tue Dec 13 09:25:55 2022
 ************************************************************************/

#include <iostream>
#include <vector>
#include <kl.h>
#include <../google_test/include/gtest/gtest.h>

TEST(graph, detla_gain) {
    int vertex_num = 8, edge_num = 13;
    std::vector<std::pair<int, int>> edges{
        {0, 1}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 5}, 
        {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {6, 7}
    };
    KL::Graph g(edge_num, edges);
    EXPECT_EQ(g.DeltaGain(2, 4), 3);
    KL::kl(g);
    EXPECT_EQ(g.DeltaGain(3, 5), 5);
}

TEST(algorithm, kl) {
    int vertex_num = 8, edge_num = 13;
    std::vector<std::pair<int, int>> edges{
        {0, 1}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 5}, 
        {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {6, 7}
    };
    KL::Graph g(vertex_num, edge_num, edges);
    std::vector<KL::PII> moves = KL::kl(g);
    ASSERT_EQ(moves.size(), 2);
    ASSERT_EQ(moves[0].first, 2);
    ASSERT_EQ(moves[0].second, 4);
    ASSERT_EQ(moves[1].first, 3);
    ASSERT_EQ(moves[1].second, 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
