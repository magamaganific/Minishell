/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:31:21 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/11 10:31:22 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal;

int	count_strings(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**copy_env(char **envp)
{
	char	**my_envp;
	int		num_strings;
	int		i;

	num_strings = count_strings(envp);
	my_envp = malloc(sizeof(char *) * (num_strings + 1));
	if (!my_envp)
		return (NULL);
	i = 0;
	while (i < num_strings)
	{
		my_envp[i] = ft_strdup(envp[i]);
		if (!my_envp[i])
		{
			free_env(my_envp);
			return (NULL);
		}
		i++;
	}
	my_envp[i] = NULL;
	return (my_envp);
}

void	built_in_exit(char *prompt)
{
	if (ft_strlen(prompt) > 4)
	{
		ft_printf("%s\n", "exit");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(prompt, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("numeric argument required", 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_printf("%s\n", "exit");
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	**my_envp;

	if (argc != 1 || argv[1])
		return (1);
	my_envp = copy_env(envp);
	while (1)
	{
		handle_signals();
		prompt = readline("minishell$ ");
		if (!prompt)
			break ;
		if (!ft_strncmp(prompt, "exit", 4))
		{
			if (prompt[4] == '\0' || prompt[4] == ' ' )
			{
				built_in_exit(prompt);
				free (prompt);
				break ;
			}
		}
		if (ft_strlen(prompt))
			add_history(prompt);
		parse_and_execute_prompt(prompt, &my_envp);
		free(prompt);
	}
	clear_history();
	free_split(my_envp);
	return (0);
}
