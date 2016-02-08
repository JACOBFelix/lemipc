/*
** ia_path_finding.c for  in /home/jacob_f/rendu/PSU_2014_lemipc/newia
**
** Made by felix jacob
** Login   <jacob_f@epitech.net>
**
** Started on  Sun Mar  8 13:07:45 2015 felix jacob
** Last update Sun Mar  8 22:26:08 2015 Arthur Poulet
*/

#include <stdlib.h>
#include "lemipc.h"

static void		path_finding(t_path path[],
				     t_pos *pos,
				     t_map map,
				     int dist)
{
  t_pos			tmp[8];
  int			tab[8];
  int			i;
  int			c;

  i = -1;
  put_in_tab(pos, tmp);
  c = 0;
  while (++i < 8)
    {
      tab[i] = -1;
      if (path[tmp[i].x + tmp[i].y * MAP_SIZE].dist > dist)
	{
	  path[tmp[i].x + tmp[i].y * MAP_SIZE].dist = dist;
	  path[tmp[i].x + tmp[i].y * MAP_SIZE].old = *pos;
	  if (map[tmp[i].x + tmp[i].y * MAP_SIZE] == NO_PLAYER)
	    path_finding(path, &tmp[i], map, dist + 1);
	    tab[c++] = i;
	}
    }
  i = -1;
  while (++i < 8 && tab[i] != -1)
    path_finding(path, &tmp[tab[i]], map, dist + 1);
}

void		init_path_finding(t_path path[], t_player *player, t_map map)
{
  int		i;

  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    {
      path[i].dist = CANT_GO;
      path[i].pos.x = i % MAP_SIZE;
      path[i].pos.y = i / MAP_SIZE;
      path[i].id_in = map[i];
      path[i].old.x = -1;
      path[i].old.y = -1;
    }
  path[player->pos.x + player->pos.y * MAP_SIZE].dist = 0;
  path_finding(path, &player->pos, map, 1);
}

static int	can_move(t_player *player,
			 t_map map)
{
  t_pos		tmp[8];
  int		i;

  put_in_tab(&player->pos, tmp);
  i = -1;
  while (++i < 8)
    {
      if (map[tmp[i].x + tmp[i].y * MAP_SIZE] == NO_PLAYER)
	return (SUCCESS);
    }
  return (FAILURE);
}

int		move_ia_forced(t_player *player,
			       t_map mpa);

int		ia_path_finding(t_player *player,
				t_map map,
				t_id type)
{
  t_path	path[MAP_SIZE * MAP_SIZE];

  if (can_move(player, map) == FAILURE)
    return (SUCCESS);
  init_path_finding(path, player, map);
  if (type == MSG_GO_TO_ENNEMY)
    return (ia_go_to_ennemy(path, player, map, 0));
  else  if (type == MSG_GO_TO_ALLY)
    return (ia_go_to_ally(path, player, map, 0));
  return (move_ia_forced(player, map));
}
