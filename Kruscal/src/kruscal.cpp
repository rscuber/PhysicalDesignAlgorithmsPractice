/*************************************************************************
	> File Name: kruscal.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Jan  2 23:28:27 2023
 ************************************************************************/

#include <iostream>
#include <cinttypes>
#include <vector>
#include <algorithm>
#include "kruscal.h"

MST::Edge::Edge(int64_t start, int64_t end, int64_t weight) 
  : start_(start), end_(end), weight_(weight) {}

MST::Graph::Graph(int64_t vertex_num, int64_t arc_num, std::vector<MST::Edge *> edgs)
  : vertex_num_(vertex_num), arc_num_(arc_num), my_union_(arc_num) {
  for (int64_t i = 0, s, e, w; i < arc_num; i++) {
    s = edgs[i]->start(), e = edgs[i]->end(), w = edgs[i]->weight();
    this->edgs_.push_back(new Edge(s, e, w));
  }
  return ;
}

void MST::Graph::InitUnion() {
  for (int64_t i = 0; i < this->my_union_.size(); i++) {
    my_union_[i] = i;
  } 
  return ;
}

int64_t MST::Graph::find(int64_t x) {
  return my_union_[x] = (my_union_[x] == x ? x : find(my_union_[x]));
}

int64_t MST::Graph::kruscal() {
  InitUnion();
  sort(edgs_.begin(), edgs_.end(), [](Edge *lhs, Edge *rhs) {
    return lhs->weight() < rhs->weight();
  });
  int64_t sum = 0, cnt = 0;
  for (int64_t i = 0; i < this->arc_num(); i++) {
    int64_t s = this->edgs_[i]->start(), e = this->edgs_[i]->end();
    int64_t fa = find(s), fb = find(e);
    if (fa - fb) {
      sum += this->edgs_[i]->weight();
      DBG("sum += %" PRId64, this->edgs_[i]->weight());
      cnt++;
      this->my_union_[fa] = fb;
      if (cnt == this->vertex_num() - 1) break;
    }
  }
  return sum; 
}

namespace {

  int64_t g_vertex_num, g_arc_num;
  std::vector<MST::Edge *> g_edgs;

  void read() {
    scanf("%" PRId64 "%" PRId64, &g_vertex_num, &g_arc_num);
    for (int64_t i = 0, s, e, w; i < g_arc_num; i++) {
      scanf("%" PRId64 "%" PRId64 "%" PRId64, &s, &e, &w);
      g_edgs.push_back(new MST::Edge(s, e, w));
    }
    return ;
  }

} // end anonymous namespace

/*
int main() {
  read();
  MST::Graph g(g_vertex_num, g_arc_num, g_edgs);
  int64_t sum = g.kruscal();
  printf("sum = %lld\n", sum > 0 ? sum : -1);
  return 0;
}
*/
