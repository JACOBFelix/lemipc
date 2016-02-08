CC	=	gcc

RM	=	rm -f

CFLAGS	+=	-Wall -Werror -Wextra -pedantic -W -I ./includes -lpthread

CFLAGS	+=	$(OPTFLAGS)

DSRCS	=	./srcs/

DSRCSAI	=	./srcs/AI/

SRCS	=	$(DSRCS)main.c \
		$(DSRCS)play.c \
		$(DSRCS)gui.c \
		$(DSRCS)client.c \
		$(DSRCS)exit_client.c \
		$(DSRCS)signal.c \
		$(DSRCS)map.c \
		$(DSRCS)game_count.c \
		$(DSRCS)player.c \
		$(DSRCS)case.c \
		$(DSRCS)ennemi.c \
		$(DSRCS)network.c \
		$(DSRCS)semaphore.c \
		$(DSRCSAI)ia_go_to.c \
		$(DSRCSAI)ia_put.c \
		$(DSRCSAI)ia_msgq.c \
		$(DSRCSAI)ia_path_finding.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	lemipc

%.o: %.c
		@printf "[\033[0;32mCompiled\033[0m] % 35s\n" $<
		@$(CC) -c -o $@ $< $(CFLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
		@printf "[\033[0;34mAssembled\033[0m] % 34s\n" $(NAME)

clean:
		@$(RM) $(OBJS)
		@printf "[\033[0;31mDeleted\033[0m] % 36s\n" $(OBJS)

fclean:		clean
		@$(RM) $(NAME)
		@printf "[\033[0;35mRemoved\033[0m] % 36s\n" $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
