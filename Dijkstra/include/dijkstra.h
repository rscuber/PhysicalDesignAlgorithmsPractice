/*************************************************************************
	> File Name: dijkstra.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Tue Jan  3 20:57:27 2023
 ************************************************************************/

#pragma once

#include "macro.h"

namespace ShortestPath {

  class Vertex {
    GETSETVAR(int64_t, num)
    GETSETVAR(int64_t, cost)
  public:
    Vertex(int64_t num, int64_t cost);
    bool operator<(const Vertex &v) const {
      if (this->cost() - v.cost()) return v.cost() < this->cost();
      return v.num() < this->num();
    }
  };

  class Arc {//邻接表存储的节点
    //终点编号，权值
    GETSETVAR(int64_t, end)
    GETSETVAR(int64_t, weight)
  public:
    Arc(int64_t end, int64_t weight);
  };

  class Graph {
    GETSETVAR(int64_t, vertex_num)
    GETSETVAR(int64_t, arc_num)
  public:
    Graph(int64_t vertex_num, int64_t arc_num, 
          const std::vector<std::vector<int64_t>> &arcs);
    std::vector<int64_t> dijkstra(int start, int end);
  private:
    std::vector<int64_t> min_cost_; //表示起点到达i点的最短路
    std::vector<std::vector<Arc *>> adjacency_list_;//用动态数组创建邻接表
  };

} // end of ShortestPath namespace
