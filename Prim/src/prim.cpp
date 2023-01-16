/*************************************************************************
	> File Name: prim.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Jan  2 23:28:27 2023
 ************************************************************************/

#include <iostream>
#include <cinttypes>
#include <vector>
#include "prim.h"

 /*
 从某一个顶点构成生成树, 每次将代价最小的新顶点纳入生成树, 直到所有顶点纳入为止。
 具体实现步骤:
    1. 选起点
    2. 在所有向外延伸的边中, 选权值最小的边;
    并将该边的终点纳入生成树(此时会有一些边变为内部边);
    循环|V| - 1 次。
 */


MST::Graph::Graph(int64_t vertex_num, 
                  int64_t arc_num, 
                  std::vector<std::vector<int64_t>> arcs) 
  : mat(vertex_num + 1, std::vector<int64_t>(vertex_num + 1, 0)),
    isJoin(vertex_num + 1, 0) {
  for (int64_t i = 0, s, e, w; i < arc_num; i++) {
    s = arcs[i][0], e = arcs[i][1], w = arcs[i][2];
    if (mat[s][e] == 0 || mat[s][e] > w) {
      mat[s][e] = mat[e][s] = w;
    }
  }
}

int64_t MST::Graph::Prim() {
    const int64_t INF = 0x3f3f3f3f3f3f3f3f;
    int64_t weight_sum = 0;
    isJoin[1] = 1; 
    for (int64_t i = 1; i < this->mat.size() - 1; i++) { // 循环|V| - 1次
      // 每次将代价最小的新顶点纳入生成树
      int64_t min_weight = INF, min_ind = 0;
      for (int64_t j = 1; j <= this->mat.size(); j++) {
        if (isJoin[j] != 1) continue;
        // 此时的j点是生成树的内部点
        for (int64_t k = 1; k <= this->mat.size(); k++) {
          if (mat[j][k] && isJoin[k] == 0 && mat[j][k] < min_weight) {
            // 1.边存在  2.为外部点  3.权值更小
            min_weight = mat[j][k];
            min_ind = k;
          }
        }
      } 
      if (min_ind == 0) return -1;
      //此时找到了代价最小的点
      weight_sum += min_weight;
      isJoin[min_ind] = 1; // 标记为内部点(已联通)
    }
    return weight_sum;
}


namespace {

  int64_t g_vertex_num, g_arc_num;
  std::vector<std::vector<int64_t>> g_arcs;

  void read() {
    scanf("%" PRId64 "%" PRId64, &g_vertex_num, &g_arc_num);
    for (int64_t i = 0, s, e, w; i < g_arc_num; i++) {
      g_arcs.push_back(std::vector<int64_t>(3, 0));
      scanf("%" PRId64 "%" PRId64 "%" PRId64 , &g_arcs[i][0], &g_arcs[i][1], &g_arcs[i][2]); 
    }
    return ;
  }

} // end anonymous namespace

/*
int main() {
  read();
  MST::Graph g(g_vertex_num, g_arc_num, g_arcs);
  int64_t sum = g.Prim();
  printf("%" PRId64 "\n", sum > 0 ? sum : -1);
  return 0;
}
*/
