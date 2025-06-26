NAME = pipex
LIB_DIR = ../
PTF_DIR = ../ft_printf

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar rcs
RM = rm -f

SRCS = main.c utils.c finders.c
OBJS = $(SRCS:.c=.o)
LIB_OBJS = $(LIB_DIR)/*.o
PTR_OBJS = $(PTF_DIR)/*.o

BP = \033[35m
NRM = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB_OBJS) $(PTR_OBJS) -o  $(NAME)
	@echo "$(BP)\n-----Expected input: <infile> <\"cmd1\"> <\"cmd2\"> <outfile>-----\n$(NRM)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus