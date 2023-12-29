CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo_bonus
SRCS = philo_utils_bonus2.c ft_atoi_unsigned_bonus.c philo_bonus.c philo_actions_bonus.c philo_monitor_bonus.c philo_utils_bonus.c philosopher_bonus.c
INCLUDES = philo_bonus.h
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS) : $(SRCS)
	cc -c $(CFLAGS) $(SRCS)

clean:
	rm -rf $(OBJS) 

fclean: clean
	rm -rf $(NAME)

re: fclean all
