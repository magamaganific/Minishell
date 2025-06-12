#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <term.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef OPTS
# define STRNG 0
# define COMMD 1
# define PIPE 2
# define REIMP 3
# define REOUT 4
# define DELIM 5
# define APPND 6
# define OPTS
#endif

#ifndef QUOTE
# define OPEN 1
# define CLOSED 0
# define QUOTE
#endif

typedef struct s_execute
{
	int	option_type;
	char	*option;
}	t_execute;

typedef struct s_prompt
{
	t_execute	*parse;
	int			quote_state;
}	t_prompt;
