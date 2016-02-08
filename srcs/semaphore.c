#include <stdio.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include "lemipc.h"

int			unlock()
{
  static struct sembuf	sem_ops = {0, 1, 0};
  static int		sem_id = -1;

  if (sem_id == -1)
    sem_id = semget(SEM_ID, SEM_NUM, S_IRUSR | S_IWUSR);
  if (sem_id == -1)
    {
      perror("Unlock init");
      return (FAILURE);
    }
#ifdef DEBUG_MODE
  printf("Unlock...\n");
#endif
  if (semop(sem_id, &sem_ops, 1) == -1)
    {
      perror("Unlock");
      return (FAILURE);
    }
#ifdef DEBUG_MODE
  printf("Unlocked\n");
#endif
  return (SUCCESS);
}

int			lock()
{
  static struct sembuf	sem_ops = {0, -1, 0};
  static int		sem_id = -1;

  if (sem_id == -1)
    sem_id = semget(SEM_ID, SEM_NUM, S_IRUSR | S_IWUSR);
  if (sem_id == -1)
    {
      perror("Lock init");
      return (FAILURE);
    }
#ifdef DEBUG_MODE
  printf("Lock...\n");
#endif
  if (semop(sem_id, &sem_ops, 1) == -1)
    {
      perror("Lock");
      return (FAILURE);
    }
#ifdef DEBUG_MODE
  printf("Locked\n");
#endif
  return (SUCCESS);
}
