/*
** ia_msgq.c for ia_msgq.c in /home/jacob_f/rendu/PSU_2014_lemipc/newia
**
** Made by felix jacob
** Login   <jacob_f@epitech.net>
**
** Started on  Sun Mar  8 13:59:51 2015 felix jacob
** Last update Sun Mar  8 23:41:15 2015 Arthur Poulet
*/

#include <stdio.h>
#include <sys/ipc.h>
#include "lemipc.h"

static void	ia_send_msg(t_player *player, t_id type)
{
  t_msgdata	data;

  send_msg(0, TEAM_MSG_ID + player->id_team, type, &data);
}

static void	what_msg_send(t_player *player, t_map map)
{
  t_path	path[MAP_SIZE * MAP_SIZE];
  int		i;

  init_path_finding(path, player, map);
  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    {
      if (map[i] == player->id_team && path[i].dist > 5
	  && i != player->pos.x + player->pos.y * MAP_SIZE)
	{
	  ia_send_msg(player, MSG_GO_TO_ALLY);
	  return ;
	}
    }
  ia_send_msg(player, MSG_GO_TO_ENNEMY);
}

int	ia_exit(t_player *player, t_map map)
{
  map[player->pos.x + player->pos.y * MAP_SIZE] = NO_PLAYER;
  return (FAILURE);
}

static int	count_nb_ennemy(t_map map, t_player *player, int *ret)
{
  int		i;

  i = -1;
  if (*ret == FAILURE)
    return (SUCCESS);
  while (++i < MAP_SIZE * MAP_SIZE)
    {
      if (map[i] != NO_PLAYER && map[i] != player->id_team)
	return (SUCCESS);
    }
  map[player->pos.x + player->pos.y * MAP_SIZE] = NO_PLAYER;
  *ret = FAILURE;
  return (FAILURE);
}

int		ia_play(t_player *player, t_map map)
{
  t_msg		msg;
  int		ret;

  lock();
  if (check_dead(player, map) == FAILURE)
    ret = FAILURE;
  else if (read_msg(CASE_DEAD_MSG_ID + player->pos.x + player->pos.y
		    * MAP_SIZE, &msg, IPC_NOWAIT) == SUCCESS)
    ret = ia_exit(player, map);
  else if (read_msg(TEAM_MSG_ID + player->id_team, &msg, IPC_NOWAIT)
	   == SUCCESS)
    {
      if (msg.type == MSG_GETOUT)
	ret = ia_exit(player, map);
      else if (msg.type == MSG_GO_TO_ALLY || msg.type == MSG_GO_TO_ENNEMY)
	ret = ia_path_finding(player, map, msg.type);
    }
  else
    {
      what_msg_send(player, map);
      ret = ia_path_finding(player, map, MSG_GO_TO_ENNEMY);
    }
  if (count_nb_ennemy(map, player, &ret) == FAILURE)
    printf("Team [%i] WON!\n", player->id_team);
  return (unlock() == SUCCESS && ret);
}
