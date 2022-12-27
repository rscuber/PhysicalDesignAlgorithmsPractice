/*************************************************************************
	> File Name: kl.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Thu Dec  8 19:32:56 2022
 ************************************************************************/

#include <iostream>
#include <vector>
#include <climits>
#include "../include/kl.h"


KL::Graph::Graph(int vertex_num, int edge_num, std::vector<PII> edges) : vertex_num_(vertex_num), edge_num_(edge_num), mat(vertex_num, std::vector<int>(vertex_num)), costs(vertex_num, 0) {
  for (auto edge : edges) {
    //undirected graph
    this->mat[edge.first][edge.second] = 1;
    this->mat[edge.second][edge.first] = 1;
  } 
  for (int i = 0; i < vertex_num; i++) {
    this->vexs.push_back(new Vertex(i));
  }
}

void KL::Graph::PrintMatrix() const {
  for (int i = 0; i < this->vertex_num(); i++) {
    for (int j = 0; j < this->vertex_num(); j++) {
      std::cout << this->mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void KL::Graph::InitialPartition() {
  for (int i = 0; i < this->vertex_num() / 2; i++) {
    this->vexs[i]->set_part(FIRST_PART); //first part
  } 
  for (int i = this->vertex_num() / 2; i < this->vertex_num(); i++) {
    this->vexs[i]->set_part(SECOND_PART); //second part
  }
  return ;
}

inline bool KL::Graph::IsFixed() const {
  for (int i = 0; i < this->vertex_num(); i++) {
    if (vexs[i]->status() == FREE) {
      return false;
    }
  }
  return true;
}

inline void KL::Graph::SetFree() {
  for (int i = 0; i < this->vertex_num(); i++) {
    vexs[i]->set_status(FREE);
  }
  return ; 
}

inline bool KL::Graph::IsSamePart(int a, int b) const {
  return vexs[a]->part() == vexs[b]->part();
}

inline bool KL::Graph::IsFree(int index) const {
  return vexs[index]->status() == FREE;
}

int KL::Graph::UpdateOneCost(int index) const {
  int cuted = 0, not_cuted = 0;
  for (int i = 0; i < this->vertex_num(); i++) {
    if (this->mat[index][i] != 1) continue;
    if (IsSamePart(index, i)) {
      not_cuted += 1;
    } else {
      cuted += 1;
    }
  }
  return cuted - not_cuted;
}

void KL::Graph::UpdateAllCosts() {
  for (int i = 0; i < this->vertex_num(); i++) {
    this->costs[i] = UpdateOneCost(i);
  }
  for (int i = 0; i < this->vertex_num(); i++) {
    DBG("%d is %s\n", i, vexs[i]->status() ? "free" : "fixed");
  }
  return ;
}

inline int KL::Graph::GetWeight(int a, int b) const {
  if (this->mat[a][b] == 0) return 0;
  else return WEIGHT;
}

inline int KL::Graph::DeltaGain(int a, int b) const {
  return this->costs[a] + this->costs[b] - 2 * GetWeight(a, b);
}

std::pair<int, std::pair<int, int>> KL::Graph::MaxGain() const {
  int a = -1, b = -1, max_detla_gain = INT_MIN;
  for (int i = 0; i < this->vertex_num(); i++) {
    for (int j = i + 1; j < this->vertex_num(); j++) {
      if (IsSamePart(i, j) || !IsFree(i) || !IsFree(j)) continue;
      int cur_detla_gain = DeltaGain(i, j);
      if (cur_detla_gain > max_detla_gain) {
        a = i, b = j;
        max_detla_gain = cur_detla_gain;
      }
    }
  } 
  return std::pair<int, std::pair<int, int>>(max_detla_gain, std::pair<int, int>(a, b));
}

inline void KL::Graph::TryMove(int a, int b) {
  this->vexs[a]->set_part(!this->vexs[a]->part());
  this->vexs[b]->set_part(!this->vexs[b]->part());
  return ;
}

inline void KL::Graph::Fix(int index) {
  this->vexs[index]->set_status(FIXED);
  return ;
}

KL::PII KL::Graph::BestMoves(const std::vector<std::pair<int, PII>> &order) const {
int max_Gm = INT_MIN, m = -1;
  std::vector<int> G;
  G.push_back(0);
  for (int i = 0; i < order.size(); i++) {
    G.push_back(G.back() + order[i].first);
    if (G.back() > max_Gm) {
      max_Gm = G.back();
      m = i;
    }
  } 
  return PII(max_Gm, m);
}

void KL::Graph::Recovery(const std::vector<std::pair<int, PII>> &order, int total, int actual) {
  for (int i = total; i > actual; i--) {
    DBG("move %c <--> %c\n", order[i].second.first + 'a', order[i].second.second + 'a')
    TryMove(order[i].second.first, order[i].second.second);
  } 
  return ;
}

void KL::Graph::PrintMoves(const std::vector<PII> &moves) const {
  for (int i = 0; i < moves.size(); i++) {
    std::cout << vexs[moves[i].first]->id() << " <--> " << vexs[moves[i].second]->id() << std::endl;
  } 
  return ;
}

void KL::Graph::RecordMoves(const std::vector<std::pair<int, KL::PII>> &order, int m, std::vector<KL::PII> &moves) {
  for (int i = 0; i <= m; i++) {
    moves.emplace_back(order[i].second); 
  }
  return ;
}

std::vector<KL::PII> KL::Graph::kl() {
  std::vector<KL::PII> moves;
  InitialPartition();
  const int INF = 0x3f3f3f3f; //infinity
  int Gm = INF; //initialize to infinity
  int i;
  while (Gm > 0) {
    DBG("new round");
    DBG("==========");
    i = 1;
    std::vector<std::pair<int, PII>> order;
    SetFree(); //set every node as free
    UpdateAllCosts(); //compute D(v) for each node
    while (!IsFixed()) { 
      //while all cells are not fixed 
      //select free node a from A and free node b from B
      //∆g = D(a) + D(b) - 2c(a, b), ∆g is maximized
      std::pair<int, std::pair<int, int>> max_g = MaxGain();  
      int a = max_g.second.first, b = max_g.second.second;
      DBG("max∆g = %d\n", max_g.first);
      order.emplace_back(max_g.first, PII(a, b)); //keep track of swapped cells
      TryMove(a, b); //actual move
      Fix(a);
      Fix(b);
      DBG("swap %c and %c\n", a + 'a', b + 'a');
      UpdateAllCosts(); //update D(v) for free node connected to a and b;(lazy)
      i = i + 1;
    }
    PII mp = BestMoves(order);//swap sequence 1...m that maximizes Gm
    Gm = mp.first;
    int m = mp.second;
    DBG("Gm = %d, m = %d\n", Gm, m + 1);
    if (Gm > 0) {
      //execute move sequences
      Recovery(order, i - 2, m);
      RecordMoves(order, m, moves);
    } 
  }
  return moves;
}

namespace {

  std::vector<std::pair<int, int>> edges;
  int v_nums, e_nums;
  void read() {
    std::cin >> v_nums >> e_nums;
    for (int i = 0, start, end; i < e_nums; i++) {
      std::cin >> start >> end;
      edges.emplace_back(start, end);
    }
    return ;
  }

} // anonymous namespace end


/*
int main() {
  read();
  KL::Graph g(v_nums, e_nums, edges);
  std::vector<KL::PII> moves = kl(g);
  std::cout << moves.size() << std::endl;
  for (auto x : moves) {
    std::cout << x.first << ", " << x.second << std::endl;
  }
  g.PrintMoves(moves);
  return 0;
}
*/
