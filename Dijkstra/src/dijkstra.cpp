/*************************************************************************
	> File Name: dijkstra.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Tue Jan  3 20:58:35 2023
 ************************************************************************/
#include <iostream>
#include <cinttypes>
#include <vector>
#include <queue>
#include "dijkstra.h"

namespace {

  int64_t g_vertex_num, g_arc_num, g_start;
  std::vector<std::vector<int64_t>> g_arcs;

  void read() {
    scanf("%" PRId64 "%" PRId64 "%" PRId64, &g_vertex_num, &g_arc_num, &g_start);
    for (int64_t i = 0, s, e, w; i < g_arc_num; i++) {
      g_arcs.push_back(std::vector<int64_t>(3, 0));
      scanf("%" PRId64 "%" PRId64 "%" PRId64 , &g_arcs[i][0], &g_arcs[i][1], &g_arcs[i][2]); 
    }
    return ;
  }

} // end anonymous namespace


const int64_t kINF = 0x3f3f3f3f3f3f3f3f;

ShortestPath::Vertex::Vertex(int64_t num, int64_t cost) 
  : num_(num), cost_(cost) {}

ShortestPath::Arc::Arc(int64_t end, int64_t weight) : end_(end), weight_(weight) {}

ShortestPath::Graph::Graph(int64_t vertex_num, int64_t arc_num, 
                 const std::vector<std::vector<int64_t>> &arcs)
  : vertex_num_(vertex_num), arc_num_(arc_num), 
    min_cost_(vertex_num + 1, kINF), adjacency_list_(vertex_num + 1) {
  for (int64_t i = 0, s, e, w; i < arc_num; i++) {
    //重边未做处理
    s = arcs[i][0], e = arcs[i][1], w = arcs[i][2];
    adjacency_list_[s].push_back(new Arc(e, w));
    adjacency_list_[e].push_back(new Arc(s, w));
  }
  for (int64_t i = 0; i < adjacency_list_.size(); i++) {
    DBG("[%" PRId64 "]: ", i);
    for (int64_t j = 0; j < adjacency_list_[i].size(); j++) {
      DBG("%" PRId64 ", %" PRId64, adjacency_list_[i][j]->end(), 
      adjacency_list_[i][j]->weight())
    }
    DBG("-------")
  }
}

std::vector<int64_t> ShortestPath::Graph::dijkstra(int start, int end) {
  std::vector<int64_t> path;
  std::vector<int64_t> parent(this->vertex_num() + 1, 0);
  std::priority_queue<ShortestPath::Vertex> q; 
  q.emplace(start, 0);
  min_cost_[start] = 0; //确定起始点的最短路径
  int cnt = this->vertex_num() - 1;
  DBG("dijkstra start");
  while (cnt) { //只需要确定|V| - 1个点的最短路即可
    ShortestPath::Vertex cur = q.top();
    q.pop(); //不能放在后面(这个点记录的距离可能并不是最短路)，需要及时pop
    if (min_cost_[cur.num()] < cur.cost()) continue;
    //已经确定最短路径的点跳过(同时也巧妙处理了重边)
    //此时选择未被确认的且最短路最小的点，以它为起点更新其他点的最短路答案
    for (int64_t i = 0; i < adjacency_list_[cur.num()].size(); i++) {
      int64_t e = adjacency_list_[cur.num()][i]->end();
      int64_t w = adjacency_list_[cur.num()][i]->weight();
      if (cur.cost() + w < this->min_cost_[e]) { 
        //可以通过中转当前节点更新e的最短路
        parent[e] = cur.num();
        this->min_cost_[e] = cur.cost() + w;
        q.emplace(e, this->min_cost_[e]);
      }
    }
    cnt--; //又确定了一个点的最短路
  }
  for (int64_t i = 1; i < min_cost_.size(); i++) {
    DBG("min_cost_[%" PRId64 " -> %" PRId64 "] = %" PRId64, start, i, min_cost_[i]);
  }
  path.push_back(end);
  for (int64_t p = parent[end]; p != 0; p = parent[p]) {
    //不断地向前找前驱来确定路径
    path.push_back(p);
    DBG("path pushback %" PRId64, parent[p])
  }
  for (int64_t l = 0, r = path.size() - 1; l < r; l++, r--) {
    //reverse
    std::swap(path[l], path[r]);
  }
  if (path[0] == end && path[0] != start) {
    path[0] = -1;
  }
  return path;
}
