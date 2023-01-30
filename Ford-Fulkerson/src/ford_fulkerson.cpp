/*************************************************************************
	> File Name: ford_fulkerson.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Jan 30 23:51:50 2023
 ************************************************************************/

#include <iostream>
#include <queue>
#include "ford_fulkerson.h"

namespace NetworkFlow {

Graph::Graph(const std::vector<std::vector<int64_t>> &residual) 
  : residual_(residual), vertex_num_(residual.size()) {}

bool Graph::bfs(int64_t source, int64_t sink, std::vector<int64_t> &parent) {
  std::vector<bool> visited(this->vertex_num(), 0);
  std::queue<int64_t> q;
  q.push(source);
  visited[source] = true;
  parent[source] = -1;
  while (!q.empty()) {
    int cur = q.front(); q.pop();
    for (int64_t i = 0; i < this->residual_[cur].size(); i++) {
      if (!visited[i] && this->residual_[cur][i] > 0) {
        q.push(i);
        parent[i] = cur;
        visited[i] = true;
      }
    }
  }
  return visited[sink] == true;
}

int64_t Graph::FordFulkerson(int64_t source, int64_t sink) {
  std::vector<int64_t> parent(this->vertex_num(), 0); //store path 
  int64_t max_flow = 0;
  //argmenting path 
  DBG("Augment the flow while tere is path from source to sink")
  while (bfs(source, sink, parent)) {
    //find minimum residual capacity of the edges along the path filled by BFS.
    int64_t path_flow = INT64_MAX;
    for (int64_t v = sink; v != source; v = parent[v]) {
      path_flow = std::min(path_flow, this->residual_[parent[v]][v]);
    }
    //update residual capacities of the edges and reverse edges along the path 
    for (int64_t v = sink; v != source; v = parent[v]) {
      this->residual_[parent[v]][v] -= path_flow;
      this->residual_[v][parent[v]] += path_flow;
    }
    //add path flow to overall flow 
    max_flow += path_flow;
  }
  return max_flow;
}

} // end of NetworkFlow 
