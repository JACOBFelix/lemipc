#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "lemipc.h"

int	main(int ac, char **av)
{
  int	shm_map_id;

  (void)ac;
  (void)av;
  srandom((long)&ac);
  if ((creat(PROJECT_FILE, S_IRWXU)) < 0)
    {
      perror("Create new project file");
      return (FAILURE);
    }
  if ((shm_map_id = shmget(MAP_ID, MAP_WEIGHT,
			   IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR)) >= 0)
    return (play(first_client(shm_map_id)));
  if ((shm_map_id = shmget(MAP_ID, MAP_WEIGHT,
			   S_IRUSR | S_IWUSR)) >= 0)
    return (play(client(shm_map_id)));
  else
    printf("Failed to run the program\n");
  return (SUCCESS);
}
