/*************************************************************************
	> File Name: ford_fulkerson.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Jan  2 23:29:47 2023
 ************************************************************************/

#pragma once

#include <cinttypes>
#include <vector>
#include "macro.h"

namespace NetworkFlow {

class Graph {
  GETSETVAR(int64_t, vertex_num)
public:
  Graph(const std::vector<std::vector<int64_t>> &residual);
  bool bfs(int64_t source, int64_t sink, std::vector<int64_t> &parent);
  int64_t FordFulkerson(int64_t source, int64_t sink);
private:
  std::vector<std::vector<int64_t>> residual_;
};

} // end of NetworkFlow 
