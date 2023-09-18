#include <iostream>

int main()
{
  unsigned int seed, count;
  signed int min, max;
  std::cin >> seed >> count >> min >> max;

  unsigned int random = seed;
  for (int i = 0; i < count; i++)
  {
    random = random xor (random << 13);

    random = random xor (random >> 17);

    random = random xor (random << 5);

    unsigned int value = min + (random % (max - min + 1));
    std::cout << value << std::endl;
  }
}