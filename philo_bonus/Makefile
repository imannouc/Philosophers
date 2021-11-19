NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

INCLUDE = philo_bonus.h

SRC = main.c\
	ft_atoi.c\
	store_options.c\
	routines_bonus.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)

re: fclean all