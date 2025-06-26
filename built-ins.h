#include <readline/readline.h>
#include <readline/history.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <signal.h>


typedef struct s_signal
{
	int	ret;
	int	ret_exit;
	int	sig;
	int ff;
}	t_signal;

extern t_signal	g_signal;

typedef	struct s_env
{
	char			*var_name;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	char	*line;
}	t_shell;