#include <string.h>
#include <stdio.h>
#include "lemipc.h"

void		curse_the_map(t_map const map)
{
  int		i;

  lock();
  CLEAN;
  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    {
      printf("%c ", map[i] == NO_PLAYER ? '-' : map[i] + '0');
      if (i % MAP_SIZE == MAP_SIZE - 1)
	printf("\n");
    }
  printf("\n");
  unlock();
}
