# Name of the executable
NAME = philo

# Compiler
CC = gcc 
CFLAGS := -Wall -Wextra -Werror -fsanitize=thread -g
LDFLAGS = -fsanitize=thread

# Source files
SRC = main.c \
	checks.c \
	philo_life.c \
	philo_init.c \
	time.c \
	run_threads.c \
	utils.c
	  
# Object files
OBJ = $(SRC:.c=.o)

# Phony targets for make commands
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Rule to link the program
$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean object files and other temporary files
clean:
	rm -f $(OBJ) $(NAME)

# Rule to fully clean the project, including the executable
fclean: clean
	rm -f $(NAME)

# Rule to re-make the project
re: fclean all
