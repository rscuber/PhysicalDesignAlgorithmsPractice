/*************************************************************************
	> File Name: prim_unittest.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Wed Dec 21 09:46:28 2022
 ************************************************************************/

#include <iostream>
#include <vector>
#include "astar.h"
#include "gtest/gtest.h"

TEST(Graph, AStarUnblockage) {
  ShortestPath::Graph grid(10, 10);
  ShortestPath::Cell start(1, 1);
  ShortestPath::Cell target(5, 5);
  std::vector<std::pair<int64_t, int64_t>> path {
    {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
    {2, 5}, {3, 5}, {4, 5}, {5, 5}
  };
  int64_t cost = 8;
  std::pair<std::vector<ShortestPath::Cell>, int64_t> ans = grid.astar(start, target);
  std::vector<ShortestPath::Cell> ans_path = ans.first;
  int64_t ans_cost = ans.second;
  for (int64_t i = 0; i < path.size(); i++) {
    EXPECT_EQ(path[i].first, ans_path[i].x());
    EXPECT_EQ(path[i].second, ans_path[i].y());
  }
  EXPECT_EQ(cost, ans_cost);
}

TEST(Graph, AStarBlockage) {
  std::vector<std::pair<int64_t, int64_t>> blocks{
    {1, 2}, {2, 2}, {3, 2}, {4, 2}
  };
  ShortestPath::Graph grid(10, 10, blocks);
  ShortestPath::Cell start(1, 1);
  ShortestPath::Cell target(5, 5);
  //grid.setBlockage(blocks);
  std::vector<std::pair<int64_t, int64_t>> path {
    {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1},
    {5, 2}, {5, 3}, {5, 4}, {5, 5}
  };
  int64_t cost = 8;
  std::pair<std::vector<ShortestPath::Cell>, int64_t> ans = grid.astar(start, target);
  std::vector<ShortestPath::Cell> ans_path = ans.first;
  int64_t ans_cost = ans.second;
  for (int64_t i = 0; i < path.size(); i++) {
    EXPECT_EQ(path[i].first, ans_path[i].x());
    EXPECT_EQ(path[i].second, ans_path[i].y());
  }
  EXPECT_EQ(cost, ans_cost);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
