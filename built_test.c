#include "built-ins.h"

t_signal g_signal;

void	ft_sigint(int sig)
{
	if (g_signal.ff == 1)
		return ;
	(void)sig;
	printf("\n");
	rl_replace_line("",1);
	rl_on_new_line();
	rl_redisplay();
	g_signal.ret = 130;
}

void	signal_man(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint);
	signal(SIGTSTP, SIG_IGN);
}

t_env	*copy_env(char **env)
{
	t_env	*copy = NULL;
	
	if (!env[0])
	{
		
	}
	while (*env)
	{
		copy->var_name = ft_strdup(*env);
		copy->prev = copy;
		copy = copy->next;
		env++;
	}
	copy->next = head;
	return (copy);
}

int	init_shell(char **av, t_shell *shell, char **env)
{
	(void)av;
	g_signal.ret = 0;
	shell->env = copy_env(env);
	if (!shell->env)
		return (0);
	return (1);
}

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	t_shell *shell = NULL;

	printf("hello");
	if (ac != 1 || !init_shell(av, shell, env))
		printf("Error\n");
	while (1)
	{
		signal_man();
		line = readline("Built-ins$ ");
		if (!line)
			break ;
		add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		free(line);
	}
	clear_history();
}