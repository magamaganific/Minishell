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
# include "Libft-42/libft.h"
# include <fcntl.h> 



/*  -------- ESTRUCTURAS --------*/


typedef struct s_zone {
	int start;
	int end;
	int expandable;
	struct s_zone *next;
}   t_zone;

typedef struct s_token {
	char *value;
	t_zone *zones;
	struct s_token *next;
}   t_token;

/* --------- PARSEO --------- */
void	parse_and_execute_prompt(char *prompt);
int		check_quotes(char *line);
int		is_metachar(char c);
int 	is_quote(char c);
t_zone *create_zone(int start, int end, int expandable);
void 	add_zone(t_token *token, t_zone *zone);
char 	*extract_token_value(char *str, int start, int end);
t_token *new_token(char *str, int start, int end);
int 	process_quoted_zone(char *str, int *i, t_token *tok);
int 	find_token_end(char *str, int i);
void 	append_token(t_token **head, t_token *new_tok);
t_token *tokenizer(char *cleaned);
void	relativize_zones(t_token *tokens, char *cleaned);
int		save_output(t_token *node);

/* --------- ERRORES ----------*/
void	error_bad_quoting(void);
void	error_syntax(char *unexpected);

/* ---------- LIBERACIÓN DE MEMORIA ---------------*/
void	free_token_list(t_token *command);
void	free_zones(t_zone *zone);
void	free_split(char **split);

#endif
