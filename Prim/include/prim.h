/*************************************************************************
	> File Name: prime.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Jan  2 23:29:47 2023
 ************************************************************************/

#pragma once

#include <cinttypes>
#include <vector>

namespace MST {

  class Graph {
  public:
    Graph(int64_t vertex_num, int64_t arc_num, std::vector<std::vector<int64_t>> arcs) ;
    int64_t Prim();
  private:
    std::vector<std::vector<int64_t>> mat;
    std::vector<int64_t> isJoin; // 标记数组: 标记内部点, 已联通(已加入生成树)
  };

}
