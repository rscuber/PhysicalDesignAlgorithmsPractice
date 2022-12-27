/*************************************************************************
	> File Name: kl_unittest.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Tue Dec 13 09:25:55 2022
 ************************************************************************/

#include <iostream>
#include <vector>
#include "kl.h"
#include "gtest/gtest.h"

TEST(Graph, InitialPartition) {
  int vertex_num = 8, edge_num = 13;
  std::vector<std::pair<int, int>> edges{
    {0, 1}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 5}, 
    {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {6, 7}
  };
  KL::Graph g(vertex_num, edge_num, edges);
  g.InitialPartition();
  EXPECT_TRUE(g.IsSamePart(0, 1));
  EXPECT_TRUE(g.IsSamePart(1, 2));
  EXPECT_TRUE(g.IsSamePart(2, 3));
  EXPECT_TRUE(g.IsSamePart(4, 5));
  EXPECT_TRUE(g.IsSamePart(5, 6));
  EXPECT_TRUE(g.IsSamePart(6, 7));
  EXPECT_TRUE(g.IsFree(0));
  EXPECT_TRUE(g.IsFree(1));
  EXPECT_TRUE(g.IsFree(2));
  EXPECT_TRUE(g.IsFree(3));
  EXPECT_TRUE(g.IsFree(4));
  EXPECT_TRUE(g.IsFree(5));
  EXPECT_TRUE(g.IsFree(6));
  EXPECT_TRUE(g.IsFree(7));
}


TEST(Graph, detla_gain) {
  int vertex_num = 8, edge_num = 13;
  std::vector<std::pair<int, int>> edges{
    {0, 1}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 5}, 
    {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {6, 7}
  };
  KL::Graph g(vertex_num, edge_num, edges);
  g.kl();
  EXPECT_EQ(g.DeltaGain(0, 6), -6);
  EXPECT_EQ(g.DeltaGain(1, 7), -6);
}

TEST(Graph, kl) {
  int vertex_num = 8, edge_num = 13;
  std::vector<std::pair<int, int>> edges{
      {0, 1}, {0, 4}, {0, 5}, {1, 4}, {1, 5}, {2, 3}, {2, 5}, 
      {2, 6}, {2, 7}, {3, 6}, {3, 7}, {4, 5}, {6, 7}
  };
  KL::Graph g(vertex_num, edge_num, edges);
  std::vector<KL::PII> moves = g.kl();
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
