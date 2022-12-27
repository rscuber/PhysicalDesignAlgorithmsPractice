/*************************************************************************
	> File Name: fm.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Sun Dec 18 17:17:07 2022
 ************************************************************************/
#pragma once

#include <cinttypes>
#include <vector>
#include <set>
#include "macro.h"

#define FREE true
#define FIXED false
#define FIRST_PART true
#define SECOND_PART false

namespace fm {
  using PII = std::pair<int64_t, int64_t>;

  class Vertex {
  public:
    explicit Vertex(int64_t id, bool status = FREE, bool part = FIRST_PART) : id_(id + 'a'), status_(status), part_(part) {}
    GETSETVAR(char, id);
    GETSETVAR(bool, status);
    GETSETVAR(bool, part);
    GETSETVAR(int64_t, area);
  };

  class Graph{
  public:
    GETSETVAR(int64_t, vertex_num);
    GETSETVAR(int64_t, edge_num);
    GETSETVAR(int64_t, max_area);
  public:
    Graph(int64_t vertex_num, 
      const std::vector<int64_t> &areas,
      const std::vector<std::vector<int64_t>> &nets);
    void InitialPartition();
    bool IsAllFixed() const;
    void SetAllFree();
    bool IsSamePart(int64_t a, int64_t b) const;
    bool IsFree(int64_t index) const;
    bool IsBelongFs(int64_t self, int64_t net_id) const;
    bool IsBelongTe(int64_t self, int64_t net_id) const;
    void UpdateGain();
    PII MaxGain(double r, double lb, double ub) const;
    void TryMove(int64_t index);
    void Fix(int64_t index);
    PII BanlanceCriterion(double r) const;
    bool IsBanlance(double lb, double ub, int index) const;
    PII BestMoves(const std::vector<PII> &order) const;
    void Recovery(const std::vector<PII> &order, int64_t total, int64_t actual);
    void RecordMoves(const std::vector<PII> &order, int m, std::vector<int64_t> &moves);
    int64_t GetCutCost() const;
    void PrintInfo() const;
    void PrintMoves(const std::vector<PII> &moves) const;
    std::vector<int64_t> FM(double r);
  private:
    std::vector<Vertex *> vexs_;
    std::vector<std::vector<int64_t>> nets_;
    std::vector<std::set<int64_t>> conn_;//which nets connect the vertex
    std::vector<int64_t> fs_;
    std::vector<int64_t> te_;
    std::vector<int64_t> gain_;
  };

} // namespace fm
