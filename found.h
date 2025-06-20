//No lo he creado yo, estoy probando.

# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>


typedef struct s_signal
{
	int					ret;
	int					ret_exit;
	int					sig;
	int					ff;
}						t_signal;

extern t_signal			g_signal;