#include <stdio.h>
#include <sys/sem.h>
#include "lemipc.h"

void		player_set(t_player *player,
			   int first,
			   t_id team_id,
			   t_pos *pos)
{
  player->first = first;
  player->id_team = team_id;
  if (pos != NULL)
    {
      player->pos.x = pos->x;
      player->pos.y = pos->y;
    }
}
