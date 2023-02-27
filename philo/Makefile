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

$(NAME): $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDE)
	gcc $(FLAGS) -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all