NAME = built-ins
CC = cc -g3 #-Wall -Werror -Wextra#
RLINE = -lreadline

LIBDIR = libft
LIBFT = libft/libft.a

SRCS = built_test.c
OBJS = $(SRCS:.c=.o)
LIBOBJS = $(LIBDIR) /*.o

all: $(NAME)

$(NAME): $(OBJS) $(LIBOBJS)
	$(CC) $(OBJS) $(RLINE) $(LIBFT) -o $(NAME)

$(LIBOBJS):
	@make -C $(LIBDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJS)
	@make clean -C $(LIBDIR)

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus