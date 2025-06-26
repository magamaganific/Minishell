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

size_t env_size(char **env)
{
	size_t i;

	i = 0;
	while(*env)
	{
		i++;
		env++;
	}
	printf("\nsize = %zu\n", i);
	return(i);
}

int init_shell(char **av, t_shell *shell, char **env)
{
	printf("\nInit_shell\n");
	t_env	*head;
	t_env	*prev;

	shell->env = (t_env *)ft_calloc(sizeof(t_env), env_size(env) + 1);
	shell->env->next = NULL;
	head = shell->env;
	while (*env)
	{
		head->var_name = *env;
		printf("saved-> %s\n", head->var_name);
		prev = head;
		head->next = head + 1;
		head++;
		head->prev = prev;
		env++;
	}
	printf("\nEnd_init\n");
	return (1);
}

void free_env(t_env *env)
{
	while (env)
	{
		free(env->var_name);
		env = env->next;
	}
}

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	t_shell shell;

	if (ac != 1 || !init_shell(av, &shell, env))
	{
		free_env(shell.env);
		printf("Error\n");
	}
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