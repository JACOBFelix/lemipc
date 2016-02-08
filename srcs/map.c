#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <stdio.h>
#include <string.h>
#include "lemipc.h"

static int		map_create_as(int const shm_map_id,
				      t_map *map,
				      int const flags)
{
  const int		sem_id = semget(SEM_ID, 1, flags);
  static struct sembuf	sem_ops = {0, 1, 0};

  if ((*map = shmat(shm_map_id, NULL, 0)) == (void *)-1)
    {
      perror("Shared memory creation");
      return (FAILURE);
    }
  if (sem_id < 0)
    {
      perror("Semaphore creation");
      return (FAILURE);
    }
  if ((flags & IPC_CREAT) && semop(sem_id, &sem_ops, 1) == FAILURE)
    {
      perror("Semaphore initialisation");
      return (FAILURE);
    }
  return (SUCCESS);
}

int		map_create_as_client(int const shm_map_id,
				     t_map *map)
{
  return (map_create_as(shm_map_id, map, S_IRUSR | S_IWUSR));
}

int		map_create_as_server(int const shm_map_id,
				     t_map *map)
{
  return (map_create_as(shm_map_id, map,
			IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR));
}

int		map_initialize(t_map map)
{
  if (map == NULL)
    return (FAILURE);
  memset(map, NO_PLAYER, MAP_WEIGHT);
  init_msg();
  return (SUCCESS);
}
