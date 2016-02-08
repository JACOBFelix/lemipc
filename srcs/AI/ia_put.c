/*
** ia_put.c for ia_put.c in /home/jacob_f/rendu/PSU_2014_lemipc/newia
**
** Made by felix jacob
** Login   <jacob_f@epitech.net>
**
** Started on  Sun Mar  8 13:12:21 2015 felix jacob
** Last update Sun Mar  8 22:29:33 2015 Arthur Poulet
*/

#include "lemipc.h"

void		check_kill(t_pos *pos, t_map map)
{
  t_pos		tmp[8];
  int		i;
  int		j;

  i = -1;
  put_in_tab(pos, tmp);
  while (++i < 8)
    {
      if (map[tmp[i].x + tmp[i].y * MAP_SIZE] != NO_PLAYER
	  && map[tmp[i].x + tmp[i].y * MAP_SIZE]
	  != map[pos->x + pos->y * MAP_SIZE])
	{
	  j = -1;
	  while (++j < 8)
	    if (j != i && map[tmp[i].x + tmp[i].y * MAP_SIZE]
		== map[tmp[j].x + tmp[j].y * MAP_SIZE])
	       {
		 send_msg(0, CASE_DEAD_MSG_ID + tmp[i].x
			  + tmp[i].y * MAP_SIZE, MSG_KILL, 0);
	       }
	}
    }
}

int		check_dead(t_player *player, t_map map)
{
  t_pos		tmp[8];
  int		i;
  int		j;

  i = -1;
  put_in_tab(&player->pos, tmp);
  while (++i < 8)
    {
      if (map[tmp[i].x + tmp[i].y * MAP_SIZE] != NO_PLAYER
	  && map[tmp[i].x + tmp[i].y * MAP_SIZE]
	  != map[player->pos.x + player->pos.y * MAP_SIZE])
	{
	  j = -1;
	  while (++j < 8)
	    if (j != i && map[tmp[i].x + tmp[i].y * MAP_SIZE]
		== map[tmp[j].x + tmp[j].y * MAP_SIZE])
	      return (ia_exit(player, map));
	}
    }
  return (SUCCESS);
}

void		put_in_tab(t_pos *pos, t_pos tab[])
{
  tab[0].x = LEFT_POS_X;
  tab[0].y = HIGH_POS_Y;
  tab[1].x = POS_X;
  tab[1].y = HIGH_POS_Y;
  tab[2].x = RIGHT_POS_X;
  tab[2].y = HIGH_POS_Y;
  tab[3].x = LEFT_POS_X;
  tab[3].y = POS_Y;
  tab[4].x = RIGHT_POS_X;
  tab[4].y = POS_Y;
  tab[5].x = LEFT_POS_X;
  tab[5].y = LOW_POS_Y;
  tab[6].x = POS_X;
  tab[6].y = LOW_POS_Y;
  tab[7].x = RIGHT_POS_X;
  tab[7].y = LOW_POS_Y;
}

void	put_in_around(t_pos pos[],
		      t_map map,
		      t_id around[])
{
  int	i;

  i = -1;
  while (++i < 8)
    around[i] = map[pos[i].x + pos[i].y * MAP_SIZE];
}
