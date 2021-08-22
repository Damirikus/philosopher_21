
NAME	= philo

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= philo.h

SRCS	= main.c chek_arguments.c utils.c realization.c

OBJS	= $(SRCS:.c=.o)
%.o: 	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(OBJS) -o ${NAME}
	
all: $(NAME)
	
clean:
	-rm -rf $(OBJS) 

fclean: clean
	-rm -rf $(NAME)
	
re:		fclean all

.PHONY: all clean fclean re
