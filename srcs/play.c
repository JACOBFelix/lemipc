#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lemipc.h"

int	play(t_client *client)
{
  if (client == NULL)
    return (FAILURE);
  if (client->player.first == 1)
    {
      while (game_count_complete_teams(client->map) < 2)
	{
	  curse_the_map(client->map);
	  usleep(100000);
	}
      while (ia_play(&client->player, client->map) == SUCCESS)
	{
	  curse_the_map(client->map);
	}
    }
  else
    {
      while (ia_play(&client->player, client->map) == SUCCESS)
	{
	  usleep(100000);
	}
    }
  if (client->player.first == 1)
    curse_the_map(client->map);
  return (SUCCESS);
}
