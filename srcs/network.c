#include <stdlib.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include "lemipc.h"

int		init_msg()
{
  static int	msq_id = -1;

  if ((msq_id = msgget(MSQ_ID, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1)
    return (FAILURE);
  return (SUCCESS);
}

int		send_msg(t_id from, long to, t_id type, t_msgdata *data)
{
  static int	msq_id = -1;
  t_msg		msg;

  if (msq_id == -1)
    if ((msq_id = msgget(MSQ_ID, S_IRUSR | S_IWUSR)) == -1)
      return (FAILURE);
  msg.from = from;
  msg.to = to;
  msg.type = type;
  if (data != NULL)
    msg.data = *data;
  else
    {
      msg.data.pos.x = 0;
      msg.data.pos.y = 0;
      msg.data.id_team = 0;
      msg.data.id_team = 0;
    }
  msgsnd(msq_id, &msg, sizeof(t_msg) - sizeof(long), 0);
  return (SUCCESS);
}

int		read_msg(t_id from, t_msg *msg, int opt_flags)
{
  static int	msq_id = -1;

  if (msq_id == -1)
    if ((msq_id = msgget(MSQ_ID, S_IRUSR | S_IWUSR)) == -1)
      return (FAILURE);
  if (msgrcv(msq_id, msg, sizeof(t_msg) - sizeof(long), from, opt_flags) < 0)
    return (FAILURE);
  return (SUCCESS);
}
