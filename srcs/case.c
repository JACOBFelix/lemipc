#include <stdlib.h>
#include "lemipc.h"

t_case		pos_to_case(t_pos const *const pos)
{
  return (pos->x + pos->y * MAP_SIZE);
}

t_pos		*case_to_pos(t_pos *const pos, t_case const idx)
{
  pos->x = idx % MAP_SIZE;
  pos->y = idx / MAP_SIZE;
  return (pos);
}

int		is_empty(t_map const map, t_pos const *const pos)
{
  if (map[pos->x + pos->y * MAP_SIZE] != 0)
    return (FAILURE);
  return (SUCCESS);
}

int		is_in_team(t_map const map,
			   t_pos const *const pos,
			   t_id const team_id)
{
  if (map[pos->x + pos->y * MAP_SIZE] != team_id)
    return (FAILURE);
  return (SUCCESS);
}
