/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:22:30 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/11 11:22:32 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*preprocess_prompt(char *prompt)
{
	char	*cleaned;

	cleaned = ft_strtrim(prompt, "\t\n\v\f\r");
	if (!cleaned || cleaned[0] == '\0')
	{
		free(cleaned);
		return (NULL);
	}
	if (!check_quotes(cleaned))
	{
		error_bad_quoting();
		free(cleaned);
		return (NULL);
	}
	return (cleaned);
}

static t_exec_unit	*generate_command_and_units(t_token **command,
					char *cleaned, char ***my_envp)
{
	t_exec_unit	*units;

	*command = tokenizer(cleaned);
	if (!*command)
		return (NULL);
	relativize_zones(*command, cleaned);
	if (add_variables_to_envp(*command, my_envp))
		return (NULL);
	expand_variables(*command, *my_envp);
	clean_tokens(*command);
	free(cleaned);
	if ((*command)->value[0] == '\0')
		return (free_token_list(*command), NULL);
	units = split_into_exec_units(*command);
	return (units);
}

static int	validate_redirections(t_exec_unit *units, t_token *command,
		char **my_envp)
{
	int	i;

	i = 0;
	while (units[i].start)
	{
		if (handle_redirections(units, i, my_envp) == -1)
		{
			free_exec_units(units);
			free_token_list(command);
			return (-1);
		}
		i++;
	}
	return (0);
}

static	int	check_end(t_exec_unit *units, t_token *command)
{
	if (is_redirection(units->start) && (!units->start->next->next))
	{
		close_fds(units);
		free_exec_units(units);
		free_token_list(command);
		return (0);
	}
	else
		return (1);
}

void	parse_and_execute_prompt(char *prompt, char ***my_envp)
{
	char		*cleaned;
	t_token		*command;
	t_exec_unit	*units;
	t_token		*aux;

	cleaned = preprocess_prompt(prompt);
	if (!cleaned)
		return ;
	units = generate_command_and_units(&command, cleaned, my_envp);
	if (!units)
		return ;
	if (validate_redirections(units, command, *my_envp) == -1)
		return ;
	if (!check_end (units, command))
		return ;
	aux = units[0].start;
	if (execute_built_in(units, my_envp))
		return (close_fds(units), free_exec_units(units),
			free_token_list(command));
	execute_units_with_pipes(units, *my_envp, &aux);
	units[0].start = aux;
	close_fds(units);
	free_exec_units(units);
	free_token_list(command);
}
