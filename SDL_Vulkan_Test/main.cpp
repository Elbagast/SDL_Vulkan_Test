#include "application.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << "START!" << std::endl;
  sdlxvulkan::Application l_application{ argc, argv };
  return l_application.execute();
}
