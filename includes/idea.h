#ifndef IDEA_H_
# define IDEA_H_

typedef struct	s_pos
{
  int		x;
  int		y;
}		t_pos;

typedef struct s_case	t_case;
typedef signed short	t_id;

typedef struct	s_case
{
  t_pos		pos;
  t_case	*neighbour[8];
  t_case	*secret_neighbour;
  t_id		id_team_occupend;
};

#endif /* IDEA_H_ */
