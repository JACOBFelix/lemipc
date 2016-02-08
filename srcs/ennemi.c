#include <stdio.h>
#include <stdlib.h>
#include "lemipc.h"

int		is_ennemi_on(t_map const map,
			     t_id const team_id,
			     t_coord const x,
			     t_coord const y)
{
  const t_case	idx = BORDERIZE(x) + BORDERIZE(y) * MAP_SIZE;

  if (map[idx] == CASE_UNUSED || map[idx] == team_id)
    return (0);
  return (1);
}

int	count_ennemi_around(t_map const map,
			    t_id const team_id,
			    t_pos const *const pos)
{
  return (is_ennemi_on(map, team_id, pos->x - 1, pos->y - 1)
	  + is_ennemi_on(map, team_id, pos->x + 0, pos->y - 1)
	  + is_ennemi_on(map, team_id, pos->x + 1, pos->y - 1)
	  + is_ennemi_on(map, team_id, pos->x - 1, pos->y + 0)
	  + is_ennemi_on(map, team_id, pos->x + 1, pos->y + 0)
	  + is_ennemi_on(map, team_id, pos->x - 1, pos->y + 1)
	  + is_ennemi_on(map, team_id, pos->x + 0, pos->y + 1)
	  + is_ennemi_on(map, team_id, pos->x + 1, pos->y + 1));
}

int		team_get_free_position(t_map const map,
				       t_id const team_id,
				       t_pos *const pos)
{
  t_case	i;
  int		n;
  int		max_ennemis_around;

  i = random() % (MAP_SIZE * MAP_SIZE);
  case_to_pos(pos, i);
  n = 0;
  max_ennemis_around = 0;
  while (map[i] != CASE_UNUSED ||
    count_ennemi_around(map, team_id, pos) > max_ennemis_around)
    {
      i = (i + 1) % MAP_SIZE;
      case_to_pos(pos, i);
      n++;
      if (n > MAP_SIZE * MAP_SIZE)
	{
	  if (max_ennemis_around == 0)
	    max_ennemis_around = 1;
	  else
	    return (FAILURE);
	}
    }
  return (SUCCESS);
}
