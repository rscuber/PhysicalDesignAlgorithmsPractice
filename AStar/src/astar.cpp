/*************************************************************************
	> File Name: astar.cpp
	> Author: 宫局仁的供橘人
	> Motto: Barefoot makes wheels
	> Created Time: Tue Jan 10 00:28:17 2023
 ************************************************************************/

#include <iostream>
#include <unordered_map>
#include <queue>
#include "astar.h"

ShortestPath::Cell::Cell() : Cell(-1, -1)  {}

ShortestPath::Cell::Cell(int64_t x, int64_t y) : x_(x), y_(y) {}

bool ShortestPath::Cell::operator==(const Cell &rhs) const {
  return this->x() == rhs.x() && this->y() == rhs.y();
}

bool ShortestPath::Cell::operator<(const Cell &rhs) const {
  if (this->x() - rhs.x()) return this->x() < rhs.x(); 
  return this->y() < rhs.y();
}

std::ostream &operator<<(std::ostream &out, const ShortestPath::Cell &c) {
  return out << "(" << c.x() << ", " << c.y() << ")";
}

size_t ShortestPath::CellHash::operator()(const Cell &c) const {
  return std::hash<int>()(c.x());
}

constexpr bool ShortestPath::CellCostGreater::operator()(
    const std::pair<Cell, int64_t> &lhs, 
    const std::pair<Cell, int64_t> &rhs 
  ) const {
  if (rhs.second - lhs.second) return rhs.second < lhs.second;
  return rhs.first < lhs.first;
}

ShortestPath::Graph::Graph(
    int64_t width, int64_t height, 
    const std::vector<std::pair<int64_t, int64_t>> &blockage
  ) : grid_(height - 1, std::vector<int64_t>(width - 1, 0)) {
  for (auto &block : blockage) {
    this->grid_[block.first][block.second] = 1;
  }
} 

inline size_t ShortestPath::Graph::height() const {
  return this->grid_.size();
}

inline size_t ShortestPath::Graph::width() const {
  return this->grid_[0].size();
}

inline bool ShortestPath::Graph::isFree(const Cell &c) const {
  return this->grid_[c.x()][c.y()] == 0;
}

inline bool ShortestPath::Graph::isValid(const Cell &c) const {
  return c.x() >= 0 && c.x() < this->height() && 
         c.y() >= 0 && c.y() < this->width() &&
         isFree(c);
}

inline void ShortestPath::Graph::setBlockage(
    const std::vector<std::pair<int64_t, int64_t>> &locations
  ) {
  for (auto &loc : locations) {
    this->grid_[loc.first][loc.second] = 1;
  }
  return ;
}

inline int64_t ShortestPath::Graph::getCost(
  const ShortestPath::Cell &lhs, 
  const ShortestPath::Cell &rhs) const {
  // Manhattan Distance
  return abs(rhs.x() - lhs.x()) + abs(rhs.y() - lhs.y()); 
}

std::vector<ShortestPath::Cell> ShortestPath::Graph::getNeighbours(const ShortestPath::Cell &cur) const {
  std::vector<ShortestPath::Cell> neighbours;
  for (int64_t i = 0; i < kDir.size(); i++) {
    int64_t x = cur.x() + kDir[i].first;
    int64_t y = cur.y() + kDir[i].second;
    if (!isValid(Cell(x, y))) continue;
    neighbours.emplace_back(x, y);
  }
  DBG("get cell(%" PRId64 ", %" PRId64 ") neighbours: ", cur.x(), cur.y());
  for (auto &cell : neighbours) {
    DBG("neighbour(%" PRId64 ", %" PRId64 ")", cell.x(), cell.y());
  }
  return neighbours;
}

void ShortestPath::Graph::getShortestPath(
  const Cell &start, const Cell &target, 
  std::unordered_map<Cell, Cell, CellHash> &came_from,
  std::vector<Cell> &path
  ) const {
  path.emplace_back(target.x(), target.y());
  for (auto &cell = came_from[target]; isValid(cell); cell = came_from[cell]) {
    // target -> start
    path.emplace_back(cell.x(), cell.y()); 
  }
  for (int64_t l = 0, r = path.size() - 1; l < r; l++, r--) {
    // reverse
    std::swap(path[l], path[r]);
  }
  return ;
}

std::pair<std::vector<ShortestPath::Cell>, int64_t>
ShortestPath::Graph::astar(
  const ShortestPath::Cell &start, 
  const ShortestPath::Cell &target
) {
  std::vector<ShortestPath::Cell> path;
  std::priority_queue<
    std::pair<Cell, int64_t>, 
    std::vector<std::pair<Cell, int64_t>>,
    CellCostGreater
  > frontier; // top: min cost
  std::unordered_map<Cell, Cell, CellHash> came_from;
  std::unordered_map<Cell, int64_t, CellHash> cost_so_far;
  frontier.emplace(start, 0);
  DBG("frontier push start(%" PRId64 ", %" PRId64 ")", start.x(), start.y());
  came_from[start] = ShortestPath::Cell(-1, -1);
  while (!frontier.empty()) {
    ShortestPath::Cell current = frontier.top().first; 
    if (current == target) break;
    for (auto &next : getNeighbours(current)) {
      int64_t new_cost = cost_so_far[current] + getCost(current, next);
      if (cost_so_far.find(next) == cost_so_far.end() || 
          new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost; 
        DBG("cost_so_far(%" PRId64 ", %" PRId64 ") = %" PRId64 "", 
            next.x(), next.y(), new_cost)
        int64_t priority = new_cost + getCost(next, target);
        frontier.emplace(next, priority);
        DBG("came_from(%" PRId64 ", %" PRId64 ") = (%" PRId64 ", %" PRId64 ")", 
            next.x(), next.y(), current.x(), current.y());
        came_from[next] = current;
      }
    }
    frontier.pop();
  } 
  getShortestPath(start, target, came_from, path);
  return std::pair<std::vector<Cell>, int64_t>(path, cost_so_far[target]);
}
