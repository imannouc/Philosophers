NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

INCLUDE = philo.h

SRC = main.c\
	ft_atoi.c\
	store_options.c\
	routines.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean:
	rm -rf $(NAME)

re: fclean all