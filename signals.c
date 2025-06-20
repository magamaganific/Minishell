
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "found.h" //la estructura de señales que he sacado del repositorio que encontré.

t_signal	g_signal;

void	ft_handle_sigint(int sig)
{
	if (g_signal.ff == 1)
		return ;
	(void)sig;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_signal.ret = 130;
}
void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN); //ctrl + d (no funciona si hay algo escrito en la linea)
	signal(SIGINT, ft_handle_sigint); //ctrl + c (el ft_handle_sigint pone el salto de linea!!!)
	signal(SIGTSTP, SIG_IGN); //ctrl + z (parece ser que no hace nada)
}

int main()
{
	char	*prompt;
	while (1)
	{
        signal_handler(); //recoge las señales en vez del propio terminal
		prompt = readline("signaltest$ ");
		if (!prompt)
			break;
		add_history(prompt);
		free(prompt);
	}
	clear_history();
    return 0;
}