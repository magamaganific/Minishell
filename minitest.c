
#include "minitest.h"

int c_is_token(int c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return(0);
}

int c_is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return(0);
}

int	exec_count(char *prompt)
{
	int	i = -1;
	int	quotes = -1;
	int execs = 0;

	while(prompt[++i])
	{
		if (prompt[i] == '"' || prompt[i] == '\'')
		{
			if (quotes == 1)
			{
				while (prompt[i] && c_is_token(prompt[i]) && c_is_space(prompt[i]));
					i++;
			}
			quotes = -quotes;
		}
		if (prompt[i] == ' ' && quotes == -1)
		{
			while (c_is_space(prompt[i + 1]))
				i++;
			execs++;
		}
	}
	execs++;
	printf("execs: %d\n", execs);
	return (execs);
}

void parse_and_execute_prompt(char *prompt)
{
	t_prompt	exec;

	exec.parse = (t_execute *)malloc(exec_count(prompt) * sizeof(t_execute));
	if (!exec.parse)
		return ;
	free(exec.parse);
}

int	main (int argc, char **argv, char **envp)
{
	char	*prompt;
	int		status;
	if (argc != 1 || argv[1])
		return (1);
	while (1)
	{
		prompt = readline("minishell$ ");
		if (!prompt) 
			break ;
		add_history(prompt);
		parse_and_execute_prompt(prompt); 
		free(prompt);
	}
	clear_history();
	return (0);
}
