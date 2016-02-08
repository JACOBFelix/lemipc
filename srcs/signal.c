#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "lemipc.h"

static void	sig_catch_catch_client(int const sig)
{
  (void)sig;
  exit(0);
}

void	sig_catch_init_client(void)
{
  printf("I catch the client !\n");
  signal(SIGINT, sig_catch_catch_client);
  signal(SIGQUIT, sig_catch_catch_client);
  signal(SIGUSR1, sig_catch_catch_client);
  signal(SIGUSR2, sig_catch_catch_client);
  signal(SIGTERM, sig_catch_catch_client);
}

static void	sig_catch_catch_first_client(int const sig)
{
  int		i;

  i = -1;
  (void)sig;
  while (++i < MAP_SIZE * MAP_SIZE)
    send_msg(0, CASE_DEAD_MSG_ID + i, MSG_GETOUT, NULL);
  exit(0);
}

void	sig_catch_init_first_client(void)
{
  printf("I catch the first client !\n");
  signal(SIGINT, sig_catch_catch_first_client);
  signal(SIGQUIT, sig_catch_catch_first_client);
  signal(SIGUSR1, sig_catch_catch_first_client);
  signal(SIGUSR2, sig_catch_catch_first_client);
  signal(SIGTERM, sig_catch_catch_first_client);
}
