#include "application.hpp"

int main(int argc, char *argv[])
{
  sdlxvulkan::Application l_application{ argc, argv };
  return l_application.execute();
}
