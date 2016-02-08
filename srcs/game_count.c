#include <string.h>
#include "lemipc.h"

int		game_count_complete_teams(t_map const map)
{
  int		i;
  int		n;
  t_id		teams[MAX_TEAM];

  memset(teams, 0, MAX_TEAM * sizeof(t_id));
  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    if (map[i] != NO_PLAYER)
      teams[map[i]]++;
  i = -1;
  n = 0;
  while (++i < MAX_TEAM)
    if (teams[i] >= 2)
      n++;
  return (n);
}

int		game_get_little_team(t_map const map)
{
  int		i;
  int		team_id;
  int		minimum_teammate;
  t_id		teams[MAX_TEAM];

  memset(teams, 0, MAX_TEAM * sizeof(t_id));
  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    if (map[i] != NO_PLAYER)
      teams[map[i]]++;
  i = -1;
  minimum_teammate = teams[0];
  team_id = 0;
  while (++i < MAX_TEAM)
    {
      if (teams[i] < minimum_teammate)
	{
	  team_id = i;
	  minimum_teammate = teams[i];
	}
    }
  return (team_id);
}

int		game_get_great_team(t_map const map)
{
  int		i;
  int		team_id;
  int		maximum_teammate;
  t_id		teams[MAX_TEAM];

  memset(teams, 0, MAX_TEAM * sizeof(t_id));
  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    if (map[i] != NO_PLAYER)
      teams[map[i]]++;
  i = -1;
  maximum_teammate = teams[0];
  team_id = 0;
  while (++i < MAX_TEAM)
    {
      if (teams[i] > maximum_teammate)
	{
	  team_id = i;
	  maximum_teammate = teams[i];
	}
    }
  return (team_id);
}

int		game_count_players(t_map const map)
{
  int		i;
  int		n;
  t_id		teams[MAX_TEAM];

  memset(teams, 0, MAX_TEAM * sizeof(t_id));
  i = -1;
  while (++i < MAP_SIZE * MAP_SIZE)
    if (map[i] != NO_PLAYER)
      teams[map[i]]++;
  i = -1;
  n = 0;
  while (++i < MAX_TEAM)
    n += teams[i];
  return (n);
}
