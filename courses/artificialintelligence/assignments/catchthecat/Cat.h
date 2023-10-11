#ifndef CAT_h
#define CAT_h
#include <queue>

#include "IAgent.h"

struct Cat : public IAgent
{
public:
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override
  {
    bool endPointFound = false;
    int distance = 0;

    //Visited Vector
    std::vector<bool> visited(world.size(), false);
    int temp = catPos.first + (catPos.second * sideSize) + ((world.size()/2));
    if(catPos.second % 2 != 0) temp--;
    visited[temp] = true;

    //Queue
    std::queue<Node> queue;
    queue.push(Node(distance, NULL, catPos.first, catPos.second));
    std::queue<std::pair<int, int>> path;


    while(!endPointFound)
    {
      auto currentNode = queue.front();
      queue.pop();

      std::vector<std::pair<int, int>> neighbors = GetNeighbors(world, {currentNode.x, currentNode.y}, sideSize);
      if(neighbors.empty())
      {
        isStuck = true;
        return {0, 0};
      }

      distance++;
      for (auto neighbor : neighbors)
      {
        int visitedIndex = neighbor.first + (neighbor.second * sideSize) + ((world.size()/2));
        if(visited[visitedIndex]) continue;
        else visited[visitedIndex] = true;

        int currentNodeIndex = currentNode.x + (currentNode.y * sideSize) + ((world.size()/2));

        queue.push(Node(distance, currentNodeIndex, neighbor.first, neighbor.second));

        std::vector<std::pair<int, int>> nextNeighbors = GetNeighbors(world, {neighbor.first, neighbor.second}, sideSize);
        if(nextNeighbors.size() > 1)
        {
          path.push(neighbor);
        }

        if(neighbor.first == sideSize / 2 * -1 || neighbor.first == sideSize / 2 || neighbor.second == sideSize / 2 * -1 || neighbor.second == sideSize / 2)
        {
          endPointFound = true;
        }
      }
    }

    return path.front();
  }

  bool isStuck = false;

private:

  struct Node
  {
    Node(int dis = 0, int last = NULL, int x = 0, int y = 0)
    {
      this->x = x;
      this->y = y;
      distance = dis;
      lastNode = last;
    }


    int distance;
    int lastNode;
    int x;
    int y;
  };

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