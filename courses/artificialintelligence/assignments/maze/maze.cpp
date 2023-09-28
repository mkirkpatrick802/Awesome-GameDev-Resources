#include <iostream>
#include <vector>
using namespace std;

struct Node
{
  Node(int x, int y)
  {
    X = x;
    Y = y;

    Walls.first = true;
    Walls.second = true;
  }

  int X;
  int Y;
  pair<bool, bool> Walls;
};

bool CheckForNeighbors(Node* CurrentNode, vector<Node*>& NeighborList, const vector<vector<Node*>>& NodeList, int Rows, int Columns);

int main()
{
  int Columns, Rows, Seed;
  const int RandomLength = 100;
  int Random[RandomLength] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  //Fill Nodes
  cin >> Columns >> Rows >> Seed;
  vector<vector<Node*>> NodeList( Rows , vector<Node*> (Columns));
  for (int i = 0; i < Rows; ++i)
  {
    for (int j = 0; j < Columns; ++j)
    {
      Node* ToCreate = new Node(j , i);
      NodeList[i][j] = ToCreate;
    }
  }

  //Depth First Search
  vector<Node*> Stack;
  Stack.push_back(NodeList[0][0]);
  while(!Stack.empty())
  {
    Node* CurrentNode = Stack.front();
    vector<Node*> NeighborList;
    if(CheckForNeighbors(CurrentNode, NeighborList, NodeList, Rows, Columns))
    {

    }
    else
    {
      Stack.erase(Stack.begin());
    }
  }

  //Build The Maze Top
  for (int i = 0; i < Columns; ++i)
  {
    if(NodeList[0][i]->Walls.second)
      cout << " " << "_";
  }

  cout << "  " << "\n";

  //Build Maze Core
  for(int i = 0; i < Rows; ++i)
  {
    for(int j = 0; j < Columns; ++j)
    {
      if(NodeList[i][j]->Walls.second)
      {
        cout << "|";
      }
      else
      {
        cout << " ";
      }

      if(i+1 < Rows)
      {
        if(NodeList[i+1][j]->Walls.first)
        {
          cout << "_";
        }
        else
        {
          cout << " ";
        }
      }
      else
      {
        cout << "_";
      }
    }

    cout << "|" << endl;
  }
}

bool CheckForNeighbors(Node* CurrentNode, vector<Node*>& NeighborList, const vector<vector<Node*>>& NodeList, int Rows, int Columns)
{

}


