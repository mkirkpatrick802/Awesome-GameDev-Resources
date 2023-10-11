#ifndef CATCHER_H
#define CATCHER_H
#include <queue>
#include "IAgent.h"

struct Catcher : public IAgent {

  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override
  {
    bool endPointFound = false;

    //Visited Vector
    std::vector<bool> visited(world.size(), false);
    int temp = catPos.first + (catPos.second * sideSize) + ((world.size()/2));
    if(catPos.second % 2 != 0) temp--;
    visited[temp] = true;

    //Queue
    std::queue<std::pair<int, int>> queue;
    queue.push(catPos);
    std::queue<std::pair<int, int>> path;

    while(!endPointFound)
    {
      auto currentNode = queue.front();
      queue.pop();

      std::vector<std::pair<int, int>> neighbors = GetNeighbors(world, currentNode, sideSize);

      for (auto neighbor : neighbors)
      {
        int visitedIndex = neighbor.first + (neighbor.second * sideSize) + ((world.size()/2));
        if(neighbor.second % 2 != 0) visitedIndex--;
        if(visited[visitedIndex]) continue;
        else visited[visitedIndex] = true;

        queue.push(neighbor);
        path.push(neighbor);
        if(neighbor.first == sideSize || neighbor.first == 0 || neighbor.second == sideSize || neighbor.second == 0)
        {
            endPointFound = true;
        }
      }
    }

      return path.back();
  }

  std::vector<std::pair<int, int>> GetNeighbors(const std::vector<bool>& world, std::pair<int,int> pos, int sideSize)
  {
      std::vector<std::pair<int, int>> neighbors;

      int posToCheck = pos.first + (pos.second * sideSize) - sideSize + ((world.size()/2) - 1);
      if(pos.second % 2 != 0) posToCheck++;
      if(!world[posToCheck])
      {
      std::pair<int, int> neighbor;

      if(pos.second % 2 != 0) neighbor.first = pos.first;
      else neighbor.first = pos.first - 1;

      neighbor.second = pos.second - 1;

      neighbors.push_back(neighbor);
      }

      posToCheck = pos.first + (pos.second * sideSize) - sideSize + 1 + ((world.size()/2) - 1);
      if(pos.second % 2 != 0) posToCheck++;
      if(!world[posToCheck])
      {
      std::pair<int, int> neighbor;

      if(pos.second % 2 != 0) neighbor.first = pos.first + 1;
      else neighbor.first = pos.first;

      neighbor.second = pos.second - 1;

      neighbors.push_back(neighbor);
      }

      posToCheck = pos.first + (pos.second * sideSize) - 1 + ((world.size()/2));
      if(pos.second % 2 != 0) posToCheck--;
      if(!world[posToCheck])
      {
      std::pair<int, int> neighbor;
      neighbor.first = pos.first - 1;
      neighbor.second = pos.second;

      neighbors.push_back(neighbor);
      }

      posToCheck = pos.first + (pos.second * sideSize) + 1 + ((world.size()/2));
      if(pos.second % 2 != 0) posToCheck--;
      if(!world[posToCheck])
      {
      std::pair<int, int> neighbor;
      neighbor.first = pos.first + 1;
      neighbor.second = pos.second;

      neighbors.push_back(neighbor);
      }

      posToCheck = pos.first + (pos.second * sideSize) + sideSize + ((world.size()/2) - 1);
      if(pos.second % 2 != 0) posToCheck++;
      if(!world[posToCheck])
      {
      std::pair<int, int> neighbor;

      if(pos.second % 2 != 0) neighbor.first = pos.first;
      else neighbor.first = pos.first - 1;

      neighbor.second = pos.second + 1;

      neighbors.push_back(neighbor);
      }

      posToCheck = pos.first + (pos.second * sideSize) + sideSize + 1 + ((world.size()/2) - 1);
      if(pos.second % 2 != 0) posToCheck++;
      if(!world[posToCheck])
      {
      std::pair<int, int> neighbor;

      if(pos.second % 2 != 0) neighbor.first = pos.first + 1;
      else neighbor.first = pos.first;

      neighbor.second = pos.second + 1;

      neighbors.push_back(neighbor);
      }

      return neighbors;
  }
};
#endif