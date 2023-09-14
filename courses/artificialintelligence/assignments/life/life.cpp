#include <iostream>

struct Cell
{
  bool alive;
  bool newValue;
};

void switchValues(Cell **cells, int n, int m)
{
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
    {
      cells[i][j].alive = cells[i][j].newValue;
    }
}

std::pair<int, int> wrapAround(int n, int m,int i, int j)
{
  if(i < 0)
    i = n;

  if(j < 0)
    j = m;

  if(i > n)
    i = 0;

  if(j > m)
    j = 0;

  return std::make_pair(i, j);
}

int getNumOfAliveNeighbors(Cell **cells, int n, int m, int i, int j)
{
  int num = 0;
  std::pair<int, int> testCords;
  n -= 1;
  m -= 1;

  testCords = wrapAround(n, m, i - 1, j - 1);
  if(cells[testCords.first][testCords.second].alive) num++;

  testCords = wrapAround(n, m, i - 1, j);
  if(cells[testCords.first][testCords.second].alive) num++;

  testCords = wrapAround(n, m, i - 1, j + 1);
  if(cells[testCords.first][testCords.second].alive) num++;

  testCords = wrapAround(n, m, i, j - 1);
  if(cells[testCords.first][testCords.second].alive) num++;

  testCords = wrapAround(n, m, i, j + 1);
  if(cells[testCords.first][testCords.second].alive) num++;

  testCords = wrapAround(n, m, i + 1, j - 1);
  if(cells[testCords.first][testCords.second].alive) num++;

  testCords = wrapAround(n, m, i + 1, j);
  if(cells[testCords.first][testCords.second].alive) num++;

  testCords = wrapAround(n, m, i + 1, j + 1);
  if(cells[testCords.first][testCords.second].alive) num++;

  return num;
}

void output(Cell **cells, int columns, int rows)
{
  //std::cout << std::endl;
  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      if (cells[i][j].alive)
        std::cout << "#";
      else
        std::cout << ".";
    }

    std::cout << std::endl;
  }
}

int main()
{
  int columns, rows, turns;
  std::cin >> rows >> columns >> turns;

  //Make 2D Array
  Cell** cells = new Cell*[columns];
  for (int i = 0; i < columns; i++)
    cells[i] = new Cell[rows];


  for (int i = 0; i < columns; i++)
    for (int j = 0; j < rows; j++)
    {
      char input;
      bool alive = false;
      std::cin >> input;
      if(input == '.')
        alive = false;
      else if(input == '#')
        alive = true;

      cells[i][j].alive = alive;
    }


  for (int t = 0; t < turns; t++)
  {
    for (int i = 0; i < columns; i++)
      for (int j = 0; j < rows; j++)
      {
        int neighbors = getNumOfAliveNeighbors(cells,columns, rows, i, j);
        bool isAlive = cells[i][j].alive;
        if(isAlive && neighbors < 2)
          cells[i][j].newValue = false;
        else if(isAlive && neighbors > 3)
          cells[i][j].newValue = false;
        else if(isAlive && (neighbors == 3 || neighbors == 2))
          cells[i][j].newValue = true;
        else if(!isAlive && neighbors == 3)
          cells[i][j].newValue = true;
        else
          cells[i][j].newValue = false;
      }

    switchValues(cells, columns, rows);
    //output(cells, columns, rows);
  }

  output(cells, columns, rows);

  return 0;
};
