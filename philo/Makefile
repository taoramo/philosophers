CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRCS = ft_atoi_unsigned.c philo.c philo_actions.c philo_monitor.c philo_utils.c philosopher.c
INCLUDES = philo.h
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
