#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "lemipc.h"

static void	remove_shared_data(void)
{
  int const	map_id = shmget(MAP_ID, MAP_WEIGHT, S_IRUSR | S_IWUSR);
  int const	sem_id = semget(SEM_ID, SEM_NUM, S_IRUSR | S_IWUSR);
  int const	msq_id = msgget(MSQ_ID, S_IRUSR | S_IWUSR);

  if (map_id < 0)
    perror("ALERT : Shared Memory is not clean");
  else
    printf("Remove Shared Memory %i > %i\n",
	   map_id, shmctl(map_id, IPC_RMID, 0));
  if (sem_id < 0)
    perror("ALERT : Semaphore is not clean");
  else
    printf("Remove Semaphore %i > %i\n",
	   map_id, semctl(sem_id, IPC_RMID, 0));
  if (msq_id < 0)
    perror("ALERT : MessageQueue is not clean");
  else
    printf("Remove MessageQueue %i > %i\n",
	   msq_id, msgctl(msq_id, IPC_RMID, 0));
}

void		exit_client(int unused, void *arg)
{
  t_client	*client;

  (void)unused;
  client = (t_client *)arg;
  free(client);
}

void		exit_first_client(int unused, void *arg)
{
  t_client	*client;
  int		i;
  int		j;
  int		n;

  (void)unused;
  client = (t_client *)arg;
  while (game_count_complete_teams(client->map) > 1)
    curse_the_map(client->map);
  i = -1;
  n = game_count_players(client->map);
  while (++i < MAX_TEAM)
    {
      j = -1;
      while (++j < n)
	send_msg(0, TEAM_MSG_ID + i, MSG_GETOUT, NULL);
    }
  while (game_count_players(client->map) > 0)
    {
      printf("Wait until every client die\n");
      usleep(100000);
    }
  remove_shared_data();
  free(client);
}
