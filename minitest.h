#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <term.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef TOKENS//opciones de input
# define OTHER 0 //No interpretables
# define COMMD 1 //commandos como "echo"
# define PIPE 2 // el pipe
# define REIMP 3 // el "<"
# define REOUT 4 // el ">"
# define DELIM 5 // el "<<"
# define APPND 6 // el ">>"
# define EXPAN 7 // el "$", si no es expandible (por estar entre '') se guardaría como "OTHER"
# define TOKENS//opciones de input
#endif

#ifndef QUOTE
# define OPEN 1
# define CLOSED 0
# define DOBLE '"'
# define SIMPLE '\''
# define QUOTE
#endif

typedef struct s_token
{
	int	option_type;
	char	*option;
}	t_token;

typedef struct s_prompt
{
	t_token	*parse;
	int			quote_state;
}	t_prompt;
