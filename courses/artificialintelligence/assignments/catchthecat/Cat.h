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
    std::queue<std::pair<int, int>> queue;
    queue.push(catPos);
    while(!endPointFound)
    {

    }

    return {0,0};
  }

  bool hasWon = false;
  bool isStuck = false;
};
#endif