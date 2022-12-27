/*************************************************************************
	> File Name: fm_unittest.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Wed Dec 21 09:46:28 2022
 ************************************************************************/

#include <iostream>
#include <vector>
#include "fm.h"
#include "gtest/gtest.h"

TEST(Graph, InitialPartition) {
  double r = 0.375;
  int64_t vex_num = 5;
  std::vector<int64_t> areas{2, 4, 1, 4, 5};
  std::vector<std::vector<int64_t>> nets{
    {0, 1}, {0, 1, 2}, {0, 3}, {0, 4}, {2, 3} 
  };
  fm::Graph g(vex_num, areas, nets);
  g.InitialPartition();
  EXPECT_TRUE(g.IsSamePart(0, 1));
  EXPECT_TRUE(g.IsSamePart(2, 3));
  EXPECT_TRUE(g.IsSamePart(3, 4));
  EXPECT_TRUE(g.IsFree(0));
  EXPECT_TRUE(g.IsFree(1));
  EXPECT_TRUE(g.IsFree(2));
  EXPECT_TRUE(g.IsFree(3));
  EXPECT_TRUE(g.IsFree(4));
}

TEST(Graph, BanlanceCriterion) {
  double r = 0.375;
  int64_t vex_num = 5;
  std::vector<int64_t> areas{2, 4, 1, 4, 5};
  std::vector<std::vector<int64_t>> nets{
    {0, 1}, {0, 1, 2}, {0, 3}, {0, 4}, {2, 3} 
  };
  fm::Graph g(vex_num, areas, nets);
  g.InitialPartition();
  fm::PII bound = g.BanlanceCriterion(r);
  EXPECT_EQ(bound.first, 1);
  EXPECT_EQ(bound.second, 11);
}

TEST(Graph, FM) {
  double r = 0.375;
  int64_t vex_num = 5;
  std::vector<int64_t> areas{2, 4, 1, 4, 5};
  std::vector<std::vector<int64_t>> nets{
    {0, 1}, {0, 1, 2}, {0, 3}, {0, 4}, {2, 3} 
  };
  fm::Graph g(vex_num, areas, nets);
  std::vector<int64_t> moves = g.FM(r);
  std::vector<int64_t> target{0, 2, 1, 3, 2, 4, 3};
  ASSERT_EQ(moves.size(), 7);
  for (int i = 0; i < moves.size(); i++) {
    ASSERT_EQ(moves[i], target[i]);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
