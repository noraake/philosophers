NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c parser.c init.c time.c actions.c simulation.c utils.c check_meals.c philo_routine.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re