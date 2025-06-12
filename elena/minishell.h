/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:22:41 by elengarc          #+#    #+#             */
/*   Updated: 2025/06/11 11:22:43 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

/*  --------ESTRUCTURAS--------*/

typedef struct s_token {
    char    *value;
    bool    quoted;
    bool    expandable;
	t_token *next;
} t_token;


/* --------- PARSEO --------- */
void	parse_and_execute_prompt(char *prompt);

#endif
