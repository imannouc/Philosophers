NAME = philo_bonus

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

INCLUDE = philo_bonus.h

SRC = main.c\
	ft_atoi.c\
	store_options.c\
	routines_bonus.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $<
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all