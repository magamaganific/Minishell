/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:42:18 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/12 10:42:20 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_bad_quoting(void)
{
	ft_putstr_fd("minishell: syntax error: bad quoting\n", 2);
}

void	error_syntax(char *unexpected)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(unexpected, 2);
	ft_putstr_fd("'\n", 2);
}
