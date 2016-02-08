/*
** ia_go_to.c for ia_go_to.c in /home/jacob_f/rendu/PSU_2014_lemipc/newia
**
** Made by felix jacob
** Login   <jacob_f@epitech.net>
**
** Started on  Sun Mar  8 13:29:35 2015 felix jacob
** Last update Sun Mar  8 22:29:21 2015 Arthur Poulet
*/

#include "lemipc.h"

static int	move(t_player *player,
		     t_map map,
		     t_pos *dest)
{
  t_pos		tmp[8];
  int		i;

  if (map[dest->x + dest->y * MAP_SIZE] != NO_PLAYER)
    return (SUCCESS);
  map[player->pos.x + player->pos.y * MAP_SIZE] = NO_PLAYER;
  map[dest->x + dest->y * MAP_SIZE] = player->id_team;
  player->pos.x = dest->x;
  player->pos.y = dest->y;
  if (check_dead(player, map) == FAILURE)
    return (ia_exit(player, map));
  put_in_tab(&player->pos, tmp);
  i = -1;
  while (++i < 8)
    check_kill(&tmp[i], map);
  return (SUCCESS);
}

static int	ia_have_a_path(t_path path[],
			       t_player *player,
			       t_map map,
			       t_pos dest)
{
  t_pos		tmp;

  tmp.x = path[dest.x + dest.y * MAP_SIZE].old.x;
  tmp.y = path[dest.x + dest.y * MAP_SIZE].old.y;
  while (path[tmp.x + tmp.y * MAP_SIZE].dist > 1)
    {
      tmp.x = path[tmp.x + tmp.y * MAP_SIZE].old.x;
      tmp.y = path[tmp.x + tmp.y * MAP_SIZE].old.y;
    }
  return (move(player, map, &tmp));
}

int		move_ia_forced(t_player *player,
			       t_map map)
{
  t_pos		tmp[8];
  int		i;

  put_in_tab(&player->pos, tmp);
  i = -1;
  while (++i < 8)
    if (map[tmp[i].x + tmp[i].y * MAP_SIZE] == NO_PLAYER)
      return (move(player, map, &tmp[i]));
  return (SUCCESS);
}

int		ia_go_to_ennemy(t_path path[],
				t_player *player,
				t_map map,
				int call)
{
  int		i;
  int		c;
  t_pos		tmp;

  i = -1;
  c = -1;
  tmp.x = -1;
  tmp.y = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    {
      if ((map[i] != player->id_team && map[i] != NO_PLAYER)
	  && (c == -1 || path[i].dist < c) && path[i].dist < CANT_GO
	  && path[i].dist > 1)
	{
	  tmp.x = i % MAP_SIZE;
	  tmp.y = i / MAP_SIZE;
	}
    }
  if (c == -1 && tmp.x == -1 && call == 0)
    return (move_ia_forced(player, map));
  else if (tmp.x == -1 && call == 1)
    return (move_ia_forced(player, map));
  return (ia_have_a_path(path, player, map, tmp));
}

int		ia_go_to_ally(t_path path[],
			      t_player *player,
			      t_map map,
			      int call)
{
  int		i;
  t_pos		tmp;
  int		c;

  c = -1;
  i = -1;
  tmp.x = -1;
  tmp.y = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    {
      if (map[i] == player->id_team
	  && (tmp.x == -1 || path[i].dist < c)
	  && path[i].dist < CANT_GO &&
	  path[i].dist > 1)
	{
	  tmp.x = i % MAP_SIZE;
	  tmp.y = i / MAP_SIZE;
	}
    }
  if (tmp.x == -1 && call == 0)
    return (move_ia_forced(player, map));
  else if (tmp.x == -1 && call == 1)
    return (move_ia_forced(player, map));
  return (ia_have_a_path(path, player, map, tmp));
}
