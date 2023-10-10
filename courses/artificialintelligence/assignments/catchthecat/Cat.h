#ifndef CAT_h
#define CAT_h
#include <queue>

#include "IAgent.h"

struct Cat : public IAgent
{
public:
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override // TODO: Uses BFS
  {
    bool endPointFound = false;

    //Visited Vector
    std::vector<bool> visited;
    visited.reserve(sideSize*sideSize);

    //Queue
    std::queue<std::pair<int, int>> queue;
    queue.push(catPos);

    //while(!endPointFound)
    {
      auto currentNode = queue.front();
      queue.pop();

      std::vector<std::pair<int, int>> neighbors = GetNeighbors(world, currentNode, sideSize);
      for (auto neighbor : neighbors)
      {

      }
    }

    return {0,0};
  }

  bool hasWon = false;
  bool isStuck = false;

private:

  std::vector<std::pair<int, int>> GetNeighbors(const std::vector<bool>& world, std::pair<int,int> pos, int sideSize)
  {
    std::vector<std::pair<int, int>> neighbors;

    int posToCheck = pos.first + pos.second - sideSize + ((world.size()/2) - 1);
    if(!world[posToCheck])
    {
        std::pair<int, int> neighbor;
        neighbor.first = pos.first - 1;
        neighbor.second = pos.second - 1;

        neighbors.push_back(neighbor);
    }

    posToCheck = pos.first + pos.second - sideSize + 1 + ((world.size()/2) - 1);
    if(!world[posToCheck])
    {
        std::pair<int, int> neighbor;
        neighbor.first = pos.first;
        neighbor.second = pos.second - 1;

        neighbors.push_back(neighbor);
    }

    posToCheck = pos.first + pos.second - 1 + ((world.size()/2));
    if(!world[posToCheck])
    {
        std::pair<int, int> neighbor;
        neighbor.first = pos.first - 1;
        neighbor.second = pos.second;

        neighbors.push_back(neighbor);
    }

    posToCheck = pos.first + pos.second + 1 + ((world.size()/2));
    if(!world[posToCheck])
    {
        std::pair<int, int> neighbor;
        neighbor.first = pos.first + 1;
        neighbor.second = pos.second;

        neighbors.push_back(neighbor);
    }

    posToCheck = pos.first + pos.second + sideSize + ((world.size()/2) - 1);
    if(!world[posToCheck])
    {
        std::pair<int, int> neighbor;
        neighbor.first = pos.first + 1;
        neighbor.second = pos.second;

        neighbors.push_back(neighbor);
    }

    posToCheck = pos.first + pos.second + sideSize + 1 + ((world.size()/2) - 1);
    if(!world[posToCheck])
    {
        std::pair<int, int> neighbor;
        neighbor.first = pos.first + 1;
        neighbor.second = pos.second;

        neighbors.push_back(neighbor);
    }

    return neighbors;
  }
};
#endif