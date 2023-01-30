/*************************************************************************
	> File Name: ford_fulkerson_unittest.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Tue Jan 31 00:26:35 2023
 ************************************************************************/

#include <iostream>
#include <vector>
#include "ford_fulkerson.h"
#include "gtest/gtest.h"

TEST(graph, FordFulkerson) {
  std::vector<std::vector<int64_t>> mat{ 
    {0, 16, 13, 0, 0, 0}, 
    {0, 0, 10, 12, 0, 0}, 
    {0, 4, 0, 0, 14, 0}, 
    {0, 0, 9, 0, 0, 20}, 
    {0, 0, 0, 7, 0, 4}, 
    {0, 0, 0, 0, 0, 0} 
  }; 
  NetworkFlow::Graph g(mat);
  EXPECT_EQ(g.FordFulkerson(0, 5), 23);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
