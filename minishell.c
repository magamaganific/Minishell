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

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	
	if (argc != 1 || argv[1])
		return (1);
	while (1)
	{
		prompt = readline("minishell$ ");
		if (!prompt)
			break ;
		add_history(prompt);
		parse_and_execute_prompt(prompt, envp);
		if (!ft_strncmp(prompt, "exit", 4))
		{
			free(prompt);
			break ;
		}
		free(prompt);
	}
	clear_history();
	return (0);
}
