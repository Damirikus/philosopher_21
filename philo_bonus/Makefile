
NAME	= philo_bonus

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= philo_bonus.h

SRCS	= main.c chek_arguments.c utils.c realization.c

OBJS	= $(SRCS:.c=.o)
%.o: 	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(OBJS) -o ${NAME}
	
bonus: $(NAME)
	
clean:
	-rm -rf $(OBJS) 

fclean: clean
	-rm -rf $(NAME)
	
re:		fclean bonus

.PHONY: bonus clean fclean re
