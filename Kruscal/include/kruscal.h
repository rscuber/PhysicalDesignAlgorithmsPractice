/*************************************************************************
	> File Name: kruscal.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Jan  2 23:29:47 2023
 ************************************************************************/

#pragma once

#include <cinttypes>
#include <vector>
#include "macro.h"

namespace MST {

  class Edge {
  GETSETVAR(int64_t, start)
  GETSETVAR(int64_t, end)
  GETSETVAR(int64_t, weight)
  public:
    Edge(int64_t start, int64_t end, int64_t weight);
  };

  class Graph {
  GETSETVAR(int64_t, vertex_num)
  GETSETVAR(int64_t, arc_num)
  public:
    Graph(int64_t vertex_num, int64_t arc_num, std::vector<Edge *> edgs);
    void InitUnion();
    int64_t find(int64_t x);
    int64_t kruscal();

  private:
    std::vector<Edge *> edgs_;
    std::vector<int64_t> my_union_;
  };

} // end of MST namespace
