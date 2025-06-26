CC = cc -Wall -Werror -Wextra
AR = ar rcs
RM = rm -f

NAME = libftprintf.a

SRCS = ft_putstr.c ft_putchar.c ft_putnbr.c ft_printf.c ft_puthex.c ft_putptr.c ft_putnbr_unsigned.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
