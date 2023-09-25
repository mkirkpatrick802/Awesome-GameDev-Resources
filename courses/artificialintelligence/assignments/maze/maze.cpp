#import <iostream>
#import <vector>

struct Node
{
  Node()
  {
    Position.first = 0;
    Position.second = 0;

    Walls.first = true;
    Walls.second = true;

  }

  Node(unsigned int X, unsigned int Y)
  {
    Position.first = X;
    Position.second = Y;

    Walls.first = true;
    Walls.second = true;
  }

  std::pair<unsigned int, unsigned int> Position;
  unsigned int Up = Position.second++;
  unsigned int Down = Position.second--;
  unsigned int Left = Position.first--;
  unsigned int Right = Position.first++;

  std::pair<bool, bool> Walls;
  bool Visited = false;
};

int main()
{
  const unsigned int ArrayLength = 100;
  unsigned int RandomNumbers[ArrayLength] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  unsigned int Columns, Rows, Index;
  std::cin >> Columns >> Rows >> Index;

  //Grid Generation
  std::vector<Node> PathNodes;
  for (int i = 0; i < Columns; ++i)
  {
    for (int j = 0; j < Rows; ++j)
    {
      Node NewNode = Node(i, j);
      PathNodes.push_back(NewNode);
    }
  }

  //Path Loop
  std::vector<Node> PathStack;
  while (!PathNodes.empty())
  {

  }

}