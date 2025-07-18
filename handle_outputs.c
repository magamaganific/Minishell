/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:14:28 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/21 18:14:30 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_redirect(char *value)
{
	if (!ft_strncmp(value, ">", 2))
		return (1);
	if (!ft_strncmp(value, ">>", 3))
		return (1);
	if (!ft_strncmp(value, "<", 2))
		return (1);
	if (!ft_strncmp(value, "<<", 3))
		return (1);
	if (!ft_strncmp(value, "|", 2))
		return (1);
	return (0);
}

int	save_output(t_token *node)
{
	int	fd_out;

	fd_out = 0;
	if (!node->next)
	{
		error_syntax("newline");
		return (-1);
	}
	if (is_invalid_redirect(node->next->value))
	{
		error_syntax(node->next->value);
		return (-1);
	}
	if (!ft_strncmp(node->value, ">>", 3))
		fd_out = open(node->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (!ft_strncmp(node->value, ">", 2))
		fd_out = open(node->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror("minishell");
		return (-1);
	}
	return (fd_out);
}
