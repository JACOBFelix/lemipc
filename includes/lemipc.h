#ifndef LEMIPC_H_
# define LEMIPC_H_

typedef signed short	t_id;
typedef signed short	t_case;
typedef t_case*		t_map;
typedef signed int	t_coord;
typedef int		t_sem_id;

# define CLEAN_STR	"\033[0;0H\033[2J\n"
# define CLEAN		printf(CLEAN_STR)
# define PLAYER_PID	player->id_player
# define PLAYER_TID	player->id_team
# define PLAYER_POSX	player->pos.x
# define PLAYER_POSY	player->pos.y

# define PROJECT_FILE	"/tmp/lemipc-jacob_f"
# define PROJECT_ID	111
# define PROJECT_MAP_ID	PROJECT_ID + 1
# define PROJECT_SEM_ID	PROJECT_ID + 2
# define PROJECT_MSQ_ID	PROJECT_ID + 3
# define MAP_ID		ftok(PROJECT_FILE, PROJECT_MAP_ID)
# define SEM_ID		ftok(PROJECT_FILE, PROJECT_SEM_ID)
# define SEM_NUM	1
# define MSQ_ID		ftok(PROJECT_FILE, PROJECT_MSQ_ID)

# define FAILURE	-1
# define SUCCESS	0

# define MAP_SIZE	24
# define MAX_PLAYER	12
# define MAX_TEAM	2
# define MAX_CASE	MAP_SIZE * MAP_SIZE

# define CASE_UNUSED	-1
# define NO_PLAYER	-1

# define LEFT_POS_X	(pos->x == 0 ? MAP_SIZE - 1 : pos->x - 1)
# define RIGHT_POS_X	(pos->x == MAP_SIZE - 1 ? 0 : pos->x + 1)
# define HIGH_POS_Y	(pos->y == 0 ? MAP_SIZE - 1 : pos->y - 1)
# define LOW_POS_Y	(pos->y == MAP_SIZE - 1 ? 0 : pos->y + 1)
# define POS_X		pos->x
# define POS_Y		pos->y

# define HIGH_LEFT_COR	LEFT_POS_X + (HIGH_POS_Y * MAP_SIZE)
# define UP		POS_X + (HIGH_POS_Y * MAP_SIZE)
# define HIGH_RIGHT_COR	RIGHT_POS_X + (HIGH_POS_Y * MAP_SIZE)
# define LEFT		LEFT_POS_X + (POS_Y * MAP_SIZE)
# define POS		POS_X + (POS_Y * MAP_SIZE)
# define RIGHT		RIGHT_POS_X + (POS_Y * MAP_SIZE)
# define LOW_LEFT_COR	LEFT_POS_X + (LOW_POS_Y * MAP_SIZE)
# define DOWN		POS_X + (LOW_POS_Y * MAP_SIZE)
# define LOW_RIGHT_COR	RIGHT_POS_X + (LOW_POS_Y * MAP_SIZE)

# define BORDER_TOP(pos)	(pos->y == 0)
# define BORDER_BOTTOM(pos)	(pos->y == MAP_SIZE - 1)
# define BORDER_LEFT(pos)	(pos->x == 0)
# define BORDER_RIGHT(pos)	(pos->x == MAP_SIZE - 1)
# define BORDERIZE(n)		(n < 0 ? MAP_SIZE + n : n)

typedef struct	s_pos
{
  t_coord	x;
  t_coord	y;
}		t_pos;

typedef struct	s_path
{
  t_pos		pos;
  int		dist;
  t_id		id_in;
  t_pos		old;
}		t_path;

typedef struct	s_path_info
{
  int		dist;
  t_id		id_team;
}		t_path_info;

typedef struct	s_player
{
  int		first;
  t_id		id_team;
  t_pos		pos;
}		t_player;

typedef struct	s_client
{
  t_map		map;
  t_player	player;
}		t_client;

union			u_semun
{
  int			val;
  struct semid_ds	*buf;
  unsigned short	*array;
};

# define MAP_WEIGHT	sizeof(t_case) * MAX_CASE
# define GAME_WEIGHT	sizeof(t_map)

int		play(t_client *client);
void		curse_the_map(t_map const map);
t_client	*first_client(int);
t_client	*client(int);
void		exit_client(int unused, void *arg);
void		exit_first_client(int unused, void *arg);
void	sig_catch_init_client(void);
void	sig_catch_init_first_client(void);
void		player_set(t_player *player,
			   int first,
			   t_id team_id,
			   t_pos *pos);
int		map_initialize(t_map);
int		map_create_as_server(int const shm_map_id,
				     t_map *map);
int		map_create_as_client(int const shm_map_id,
				     t_map *map);
int		game_count_complete_teams(t_map const map);
int		game_get_little_team(t_map const map);
int		game_get_great_team(t_map const map);
int		game_count_players(t_map const map);
t_case		pos_to_case(t_pos const *const);
t_pos		*case_to_pos(t_pos *const pos,
			     t_case const idx);
int		is_empty(t_map const map,
			 t_pos const *const pos);
int		is_in_team(t_map const map,
			   t_pos const *const pos,
			   t_id const team_id);
int		is_ennemi_on(t_map const,
			     t_id const team_id,
			     t_coord const x,
			     t_coord const y);
int		count_ennemi_around(t_map const,
				    t_id const team_id,
				    t_pos const *const pos);
int		team_get_free_position(t_map const,
				       t_id const team_id,
				       t_pos *const pos);
int		unlock();
int		lock();

# define TEAM_MSG_ID		29558
# define PLAYER_MSG_ID		39558
# define CASE_MSG_ID		49558
# define CASE_DEAD_MSG_ID	59558
# define MSG_KO		0
# define MSG_OK		1
# define MSG_MOVE	2
# define MSG_KILL	3
# define MSG_GETOUT	6
# define FLEE		7
# define FRAG		8
# define MSG_GO_TO_ALLY	14
# define MSG_GO_TO_ENNEMY 15
# define HANDLE		9
# define MOVE		10
# define CANT_GO        3000
typedef struct	s_msgdata
{
  t_pos		pos;
  t_id		id_player;
  t_id		id_team;
}		t_msgdata;

typedef struct	s_msg
{
  long		to;
  t_id		type;
  t_id		from;
  t_msgdata	data;
}		t_msg;
int		init_msg();
int		read_msg(t_id from, t_msg *msg, int opt_flags);
int		send_msg(t_id from, long to, t_id type, t_msgdata *data);
int		player_leave(t_player *player);
int		player_connexion_to_server(t_player *player);
void		put_in_tab(t_pos *pos, t_pos tab[]);
int		check_dead(t_player *player, t_map map);
void		check_kill(t_pos *pos, t_map map);
int		ia_path_finding(t_player *player,
				t_map map,
				t_id type);
void		init_path_finding(t_path path[],
				  t_player *player,
				  t_map map);
int		ia_go_to_ally(t_path path[],
			      t_player *player,
			      t_map map,
			      int call);
int		ia_go_to_ennemy(t_path path[],
				t_player *player,
				t_map map,
				int call);
int		ia_play(t_player *player, t_map map);
int		ia_exit(t_player *player, t_map map);

#endif /* !LEMIPC_H_ */
