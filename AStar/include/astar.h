/*************************************************************************
	> File Name: astar.h
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Mon Jan  2 23:29:47 2023
 ************************************************************************/

#pragma once

#include <unordered_map>
#include <cinttypes>
#include <vector>
#include "macro.h"

namespace ShortestPath {

class Cell {
  GETSETVAR(int64_t, x)
  GETSETVAR(int64_t, y)
public:
  Cell();
  Cell(int64_t x, int64_t y);
  bool operator==(const Cell &rhs) const;
  bool operator<(const Cell &rhs) const;
};

struct CellHash {
  size_t operator()(const Cell &c) const;
};

struct CellCostGreater {
  constexpr bool operator()(const std::pair<Cell, int64_t> &lhs, 
                            const std::pair<Cell, int64_t> &rhs) const;
};

class Graph {
public:
  const std::vector<std::pair<int64_t, int64_t>> kDir{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
  };
  Graph(int64_t width, int64_t height, 
        const std::vector<std::pair<int64_t, int64_t>> &blockage = 
        std::vector<std::pair<int64_t, int64_t>>());

  size_t height() const;
  size_t width() const;
  bool isFree(const Cell &c) const;
  bool isValid(const Cell &c) const;

  void setBlockage(const std::vector<std::pair<int64_t, int64_t>> &locations);

  int64_t getCost(const Cell &lhs, const Cell &rhs) const;
  std::vector<ShortestPath::Cell> getNeighbours(const ShortestPath::Cell &cur) const;
  void getShortestPath(
    const Cell &start, const Cell &target, 
    std::unordered_map<Cell, Cell, CellHash> &came_from,
    std::vector<Cell> &path
  ) const ;

  std::pair<std::vector<Cell>, int64_t> astar(
    const ShortestPath::Cell &start, 
    const ShortestPath::Cell &target
  );
private:
  std::vector<std::vector<int64_t>> grid_; // 0: free,  1: blockage
};

} // end of ShortestPath
