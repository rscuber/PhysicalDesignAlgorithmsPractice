/*************************************************************************
	> File Name: kl.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Tue Dec 13 09:35:59 2022
 ************************************************************************/

#ifndef _KL_H
#define _KL_H

#include "macro.h"

#define FREE true
#define FIXED false
#define FIRST_PART true
#define SECOND_PART false
#define WEIGHT 1

namespace KL {
  using PII = std::pair<int, int>;

  class Vertex {
  public:
    Vertex(int id, bool status = FREE, bool part = FIRST_PART) : id_(id + 'a'), status_(status), part_(part) {}
    GETSETVAR(char, id);
    GETSETVAR(bool, status);
    GETSETVAR(bool, part);
  };

  class Graph{
  public:
    GETSETVAR(int, vertex_num);
    GETSETVAR(int, edge_num);
  public:
    Graph(int vertex_num, int edge_num, std::vector<PII> edges);
    void PrintMatrix() const;
    void InitialPartition();
    bool IsFixed() const;
    void SetFree();
    bool IsSamePart(int a, int b) const;
    bool IsFree(int index) const;
    int UpdateOneCost(int index) const;
    void UpdateAllCosts();
    int GetWeight(int a, int b) const;
    int DeltaGain(int a, int b) const;
    std::pair<int, std::pair<int, int>> MaxGain() const;
    void TryMove(int a, int b);
    void Fix(int index);
    PII BestMoves(const std::vector<std::pair<int, PII>> &order) const;
    void Recovery(const std::vector<std::pair<int, PII>> &order, int total, int actual);
    void RecordMoves(const std::vector<std::pair<int, KL::PII>> &order, int m, std::vector<KL::PII> &moves);
    std::vector<PII> kl();
    void PrintMoves(const std::vector<PII> &moves) const;
private:
    std::vector<std::vector<int>> mat; //adjcency matrix
    std::vector<Vertex *> vexs;
    std::vector<int> costs;
  };

  void read();

  void RecordMoves(const std::vector<std::pair<int, PII>> &order, int m, std::vector<PII> &moves);

  std::vector<PII> kl(Graph &g);

}; // namespace KL

#endif
