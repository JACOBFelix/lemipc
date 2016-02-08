#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lemipc.h"

static t_client	*free_unlock_retnull(t_client *client)
{
  free(client);
  unlock();
  return (NULL);
}

t_client	*first_client(int shm_map_id)
{
  t_client	*client;

  if ((client = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  lock();
  if (map_create_as_server(shm_map_id, &client->map) == FAILURE)
    return (free_unlock_retnull(client));
  if (map_initialize(client->map) == FAILURE)
    return (free_unlock_retnull(client));
  client->player.first = 1;
  client->player.pos.x = MAP_SIZE / 2;
  client->player.pos.y = MAP_SIZE / 2;
  client->player.id_team = 0;
  client->map[pos_to_case(&client->player.pos)] = 0;
  on_exit(exit_first_client, client);
  unlock();
  return (client);
}

t_client	*client(int shm_map_id)
{
  t_client	*client;
  t_pos		pos;

  if ((client = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  lock();
  if (map_create_as_client(shm_map_id, &client->map) == FAILURE
      || init_msg() == FAILURE
      || game_count_players(client->map) >= MAX_PLAYER)
    return (free_unlock_retnull(client));
  player_set(&client->player, 0, game_get_little_team(client->map), NULL);
  if (team_get_free_position(client->map, client->player.id_team, &pos)
      == SUCCESS)
    {
      client->player.pos.x = pos.x;
      client->player.pos.y = pos.y;
    }
  else
    return (free_unlock_retnull(client));
  client->map[client->player.pos.x
	      + client->player.pos.y * MAP_SIZE] = client->player.id_team;
  on_exit(exit_client, client);
  unlock();
  return (client);
}
