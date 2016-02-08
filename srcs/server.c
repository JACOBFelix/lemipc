#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "lemipc.h"

static void	gui_start_curses(t_map map, t_id teams[])
{
  int		i;

  while (game_count_complete_teams(teams) > 1)
    {
      CLEAN;
      printf("%i teams alive\n", game_count_complete_teams(teams));
      i = -1;
      while (++i < MAP_SIZE * MAP_SIZE)
	{
	  printf("%c ", map[i] == NO_PLAYER ? '-' : map[i] + '0');
	  if (i % MAP_SIZE == MAP_SIZE - 1)
	    printf("\n");
	}
      printf("\n");
      usleep(100000);
    }
  CLEAN;
  printf("The team %i won the game\n", game_get_great_team(teams));
}

static void		remove_players(int unused, void *arg)
{
  t_serverdata		*data;
  int			i;
  int			n;

  (void)unused;
  data = (t_serverdata *)arg;
  i = -1;
  while (++i < MAX_TEAM)
    {
      n = -1;
      while (++n < data->teams[i])
	send_msg(SERVER_MSG_ID, TEAM_MSG_ID + i, MSG_GETOUT, NULL);
    }
}

int		fg_server(t_serverdata *data)
{
  pthread_t	bg_server;

  printf("Server is running (max_player: %i)...\n", MAX_PLAYER);
  on_exit(&remove_players, data);
  atexit(&remove_shm);
  server_sig_catch_init();
  if (pthread_create(&bg_server, NULL, &bg_server_accept, data) != 0)
    return (FAILURE);
  while (game_count_complete_teams(data->teams) < 2)
    usleep(100000);
  while (game_count_complete_teams(data->teams) > 1)
    {
      gui_start_curses(data->map, data->teams);
    }
  pthread_detach(bg_server);
  printf("Shutdown server ...\n");
  return (SUCCESS);

}

void		*bg_server_accept(void *arg)
{
  t_serverdata	*data;

  data = (t_serverdata *)arg;
  read_player_connexions(data->map, data->teams);
  return ((void *)0);
}

int		server(int shm_map_id)
{
  t_serverdata	data;
  pid_t		pid;

  if ((game_create_as_server(shm_map_id, &data.map)) == FAILURE)
    return (FAILURE);
  if (game_initialize(data.map, data.teams) == FAILURE)
    return (FAILURE);
  pid = fork();
  if (pid == 0)
    return (client(shm_map_id));
  else
    return (fg_server(&data));
}
