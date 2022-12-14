/*************************************************************************
	> File Name: prim_unittest.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Wed Dec 21 09:46:28 2022
 ************************************************************************/

#include <iostream>
#include <vector>
#include "prim.h"
#include "gtest/gtest.h"

TEST(Graph, Prim) {
  int64_t g_vertex_num = 5, g_arc_num = 6;
  std::vector<std::vector<int64_t>> g_arcs{
    {1, 2, 3},
    {3, 5, 1},
    {2, 4, 6},
    {4, 1, 1},
    {2, 3, 9},
    {2, 3, 1}
  };
  MST::Graph g(g_vertex_num, g_arc_num, g_arcs);
  EXPECT_EQ(g.Prim(), 6);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
