/*************************************************************************
	> File Name: prim_unittest.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Wed Dec 21 09:46:28 2022
 ************************************************************************/

#include <iostream>
#include <vector>
#include "dijkstra.h"
#include "gtest/gtest.h"

TEST(Graph, dijkstra) {
  int64_t g_vertex_num = 6, g_arc_num = 6, g_start = 1;
  std::vector<std::vector<int64_t>> g_arcs = {
    {1, 2, 3},
    {3, 5, 1},
    {2, 4, 6},
    {4, 1, 1},
    {2, 3, 9},
    {2, 3, 1}
  };
  std::vector<std::vector<int64_t>> g_path = {
    {1}, 
    {1, 2},
    {1, 2, 3},
    {1, 4},
    {1, 2, 3, 5},
    {-1}
  };
  for (int64_t i = 0; i < g_vertex_num; i++) {
    ShortestPath::Graph g(g_vertex_num, g_arc_num, g_arcs);
    std::vector<int64_t> ans_path = g.dijkstra(g_start, i + 1);
    for (int64_t j = 0; j < g_path[i].size(); j++) {
      EXPECT_EQ(ans_path[j], g_path[i][j]);
    }
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
