/*************************************************************************
	> File Name: fm.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Dec 19 14:26:37 2022
 ************************************************************************/

#include <iostream>
#include "../include/fm.h"
using namespace std;

fm::Graph::Graph(int64_t vertex_num, 
                 const std::vector<int64_t> &areas, 
                 const std::vector<std::vector<int64_t>> &nets)
  : vertex_num_(vertex_num), 
    conn_(vertex_num, std::set<int64_t>()),
    fs_(vertex_num),
    te_(vertex_num),
    gain_(vertex_num),
    max_area_(0) {
  for (int64_t i = 0; i < nets.size(); i++) {
    this->nets_.emplace_back(nets[i]);
    for (int64_t j = 0; j < nets[i].size(); j++) {
      DBG("insert %" PRId64 " to conn[%" PRId64 "]", i, nets[i][j])
      this->conn_[nets[i][j]].insert(i);
    }
  }
  for (int64_t i = 0; i < this->vertex_num(); i++) {
    this->vexs_.push_back(new fm::Vertex(i)); 
    this->vexs_[i]->set_area(areas[i]);
    if (vexs_[i]->area() > this->max_area()) {
      this->set_max_area(vexs_[i]->area());
    }
  }
}

inline void fm::Graph::InitialPartition() {
  for (int64_t i = 0; i < 2; i++) {
    this->vexs_[i]->set_part(FIRST_PART);
  }
  for (int64_t i = 2; i < 5; i++) {
    this->vexs_[i]->set_part(SECOND_PART);
  }
  return ;
}

inline bool fm::Graph::IsAllFixed() const {
  for (int64_t i = 0; i < this->vertex_num(); i++) {
    if (this->vexs_[i]->status() == FREE) return false;
  }
  return true;
}

inline void fm::Graph::SetAllFree() {
  for (int64_t i = 0; i < this->vertex_num(); i++) {
    this->vexs_[i]->set_status(FREE);
  }
  return ;
}

inline bool fm::Graph::IsSamePart(int64_t a, int64_t b) const {
  return this->vexs_[a]->part() == this->vexs_[b]->part();
}

inline bool fm::Graph::IsFree(int64_t index) const {
  return this->vexs_[index]->status() == FREE;
}

inline bool fm::Graph::IsBelongFs(int64_t self, int64_t net_id) const {
  for (auto cell : nets_[net_id]) {
    if (cell == self) continue;
    if (!IsSamePart(self, cell)) continue;
    return false;
  } 
  DBG("N%" PRId64 " is one of the FS nets of %c", net_id + 1, 'a' + (int)self)
  return true;
}

inline bool fm::Graph::IsBelongTe(int64_t self, int64_t net_id) const {
  for (auto cell : nets_[net_id]) {
    if (cell == self) continue;
    if (IsSamePart(self, cell)) continue;
    return false;
  } 
  DBG("N%" PRId64 " is one of the TE nets of %c", net_id + 1, (int)self + 'a')
  return true;
}

void fm::Graph::UpdateGain() {
  DBG(L_YELLOW "update info for each free cell\n")
  for (int64_t i = 0; i < this->vertex_num(); i++) {
    if (!IsFree(i)) continue;
    int64_t f = 0, t = 0;
    for (auto net_id : conn_[i]) {
      if (IsBelongFs(i, net_id)) f++;
      else if (IsBelongTe(i, net_id)) t++;
    }
    fs_[i] = f;
    te_[i] = t;
    gain_[i] = fs_[i] - te_[i];
    DBG("FS(%c) = %" PRId64 "\t TE(%c) = %" PRId64 "\t ∆g(%c) = %" PRId64"\n", (int)i + 'a', fs_[i], (int)i + 'a', te_[i], (int)i + 'a', gain_[i]);
  } 
  return ;
}

fm::PII fm::Graph::MaxGain(double r, double lb, double ub) const {
  int64_t max_index = -1, max_gain = INT64_MIN;
  for (int64_t i = 0; i < this->vertex_num(); i++) {
    if (!IsFree(i)) continue;
    if (gain_[i] > max_gain && IsBanlance(lb, ub, i)) {
      max_index = i; 
      max_gain = gain_[i];
    }
  } 
  DBG("Get max ∆g(%c) = %" PRId64 "\n", (int)max_index + 'a', gain_[max_index]);
  return fm::PII(max_index, gain_[max_index]);
}

inline void fm::Graph::TryMove(int64_t index) {
  vexs_[index]->set_part(!vexs_[index]->part());
  DBG("Move %c\n", (int)index + 'a')
  return ;
}

void fm::Graph::Fix(int64_t index) {
  this->vexs_[index]->set_status(FIXED); 
  DBG(L_PINK "Fix %c\n", (int)index + 'a')
  return ;
}

fm::PII fm::Graph::BestMoves(const std::vector<fm::PII> &order) const {
  int64_t max_Gm = INT64_MIN, m = -1;
  std::vector<int64_t> G;
  G.push_back(0);
  for (int i = 0; i < order.size(); i++) {
    G.push_back(G.back() + order[i].second);
    if (G.back() >= max_Gm) {
      m = i;
      max_Gm = G.back();
    }
  }
  return fm::PII(m, max_Gm);
}

fm::PII fm::Graph::BanlanceCriterion(double r) const {
  double area_A = 0, area_B = 0, max_area = 0;
  for (int64_t i = 0; i < this->vertex_num(); i++) {
    if (vexs_[i]->area() > max_area) {
      max_area = vexs_[i]->area();
    }
    if (vexs_[i]->part() == FIRST_PART) {
      area_A += vexs_[i]->area();
    } else {
      area_B += vexs_[i]->area();
    }
  }
  double area_V = area_A + area_B;
  double lb = r * area_V - max_area;
  double ub = r * area_V + max_area;
  return fm::PII(lb, ub);
}

bool fm::Graph::IsBanlance(double lb, double ub, int index) const {
  double area_A = 0, area_B = 0, max_area = 0;
  for (int64_t i = 0; i < this->vertex_num(); i++) {
    if (vexs_[i]->area() > max_area) {
      max_area = vexs_[i]->area();
    }
    if (vexs_[i]->part() == FIRST_PART) {
      area_A += vexs_[i]->area();
    } else {
      area_B += vexs_[i]->area();
    }
  }
  if (vexs_[index]->part() == FIRST_PART) {
    area_A -= vexs_[index]->area();    
    area_B += vexs_[index]->area();    
  } else {
    area_A += vexs_[index]->area();    
    area_B -= vexs_[index]->area();    
  }
  return lb <= area_A && area_A <= ub;
}

void fm::Graph::Recovery(const std::vector<fm::PII> &order, int64_t total, int64_t actual) {
  for (int64_t i = total; i > actual; i--) {
    TryMove(order[i].first);
  } 
  return ;
}

void fm::Graph::RecordMoves(const std::vector<fm::PII> &order, int m, std::vector<int64_t> &moves) {
  for (int i = 0; i <= m; i++) {
    moves.push_back(order[i].first);
  } 
  return ;
}

int64_t fm::Graph::GetCutCost() const {
  int cuted = 0;
  for (int64_t i = 0; i < nets_.size(); i++) {
    bool part = vexs_[nets_[i][0]]->part(), flag = true;
    for (auto cell_id : nets_[i]) {
      if (vexs_[cell_id]->part() == part) continue; 
      flag = false;
      break;
    }
    if (!flag) cuted++;
  } 
  return cuted;
}

void fm::Graph::PrintInfo() const {
  for (auto x : vexs_) {
    std::cout << x->id() << " ";
    if (x->part()) {
      std::cout << "A ";
    } else {
      std::cout << "B ";
    }
    if (x->status()) {
      std::cout << "FREE " << std::endl;
    } else {
      std::cout << "FIXED" << std::endl;
    }
  }
  return ;
}

std::vector<int64_t> fm::Graph::FM(double r) {
  std::vector<int64_t> moves;
  const int64_t kINF = 0x3f3f3f3f;
  int64_t Gm = kINF;
  fm::PII bound = BanlanceCriterion(r);
  int64_t lb = bound.first, ub = bound.second;
  InitialPartition();
  int64_t cut_cost = GetCutCost();
  int round = 0;
  while (Gm > 0) {
    round++;
    DBG(L_YELLOW "Pass %d\n", round);
    int64_t i = 1;
    std::vector<fm::PII> order;
    SetAllFree();
    //PrintInfo();
    UpdateGain();
    while (!IsAllFixed()) {
      fm::PII p = MaxGain(r, lb, ub); //find the cell with maximum gain
      int64_t cell = p.first, detla_gain = p.second;
      order.emplace_back(cell, detla_gain); //keep track of cells moved
      TryMove(cell);
      Fix(cell); //mark cell as fixed
      //PrintInfo();
      UpdateGain(); //update gains for critical cells
      i = i + 1;
    }
    fm::PII pm = BestMoves(order);
    int64_t m = pm.first; 
    Gm = pm.second;
    DBG("m = %" PRId64 ", Gm = %" PRId64, m + 1, Gm)
    if (Gm > 0) {
      Recovery(order, i - 2, m); 
      RecordMoves(order, m, moves);
    }
    DBG(L_RED "cut_cost from %" PRId64 " to %" PRId64, cut_cost, GetCutCost());
    cut_cost = GetCutCost();
  }
  return moves;
}

namespace {

  int g_vex_num, g_net_num;
  double g_r;
  std::vector<std::vector<int64_t>> nets;
  std::vector<int64_t> areas;

  void read() {
    std::cin >> g_r;
    std::cin >> g_vex_num;
    for (int64_t i = 0, area; i < g_vex_num; i++) {
      std::cin >> area;
      areas.push_back(area);
    }
    std::cin >> g_net_num;
    for (int64_t i = 0, num; i < g_net_num; i++) {
      std::cin >> num;
      nets.push_back(std::vector<int64_t>());
      for (int j = 0, cell_id; j < num; j++) {
        std::cin >> cell_id;
        nets[i].push_back(cell_id);
      }
    }
  }

} // end anonymous namespace

/*
int main() {
  read();
  fm::Graph g(g_vex_num, areas, nets);
  DBG("graph construct success.")
  vector<int64_t> m = g.FM(g_r);
  DBG(L_YELLOW "FM ends.\n")
  DBG(L_CYAN "moves: ");
  for (auto x : m) {
    printf("%" PRId64 " ", x);
  }
  printf("\n");
  return 0;
}
*/
